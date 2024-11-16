# new better build system
import os
import argparse
import platform
import shutil

parser = argparse.ArgumentParser(description="Example of adding custom flags.")
parser.add_argument('-b', '--boot', action='store_true', help="boots the os.")
parser.add_argument('-g', '--nogrub', action='store_true', help="compiles only, doesn't run grub-mkrescue.")


def clear_folder(folder_path):
    # Check if the folder exists
    if os.path.exists(folder_path):
        # Delete all files and subdirectories in the folder
        for filename in os.listdir(folder_path):
            file_path = os.path.join(folder_path, filename)
            try:
                if os.path.isfile(file_path) or os.path.islink(file_path):
                    os.unlink(file_path)  # Remove file or symlink
                elif os.path.isdir(file_path):
                    shutil.rmtree(file_path)  # Remove directory
            except Exception as e:
                print(f"Failed to delete {file_path}. Reason: {e}")
    else:
        print("Folder does not exist.")

clear_folder("build")
args = parser.parse_args()
def get_all_files(directory):
    files_with_extension = []
    files_without_extension = []
    
    for root, _, files in os.walk(directory):
        for file in files:
            # File path with extension (including folder names)
            file_with_extension = os.path.relpath(os.path.join(root, file), directory)
            # Filename without extension
            filename_without_extension = os.path.splitext(file)[0]
            file_without_extension = filename_without_extension  # Just the file name without path
            
            # Add both versions to the respective lists
            files_with_extension.append(file_with_extension)
            files_without_extension.append(file_without_extension)
    
    return files_with_extension, files_without_extension
build_directory_path = os.getcwd()+"/build"

if not os.path.exists(build_directory_path):
    # Create the directory
    os.makedirs(build_directory_path)
    print(f"Directory created: {build_directory_path}")
else:
    print(f"Directory already exists: {build_directory_path}")



exit_code = os.system(f"i686-elf-gcc --version")
if exit_code != 0:
    print("install i686-elf")
    quit()

exit_code = os.system(f"nasm --version")
if exit_code != 0:
    print("install nasm")
    quit()

exit_code = os.system(f"grub-mkrescue --version")
if exit_code != 0:
    print("install nasm")
    quit()

if args.boot:
    os.system("qemu-system-x86_64 --version")
    if exit_code != 0:
        print("install qemu")
        quit()
directory_path = os.getcwd()+"/src"
files_to_build, files_to_build_no_extensions = get_all_files(directory_path)


asm_path = os.getcwd()+"/asm"
asm_to_build,asm_to_build_no_extensions =  get_all_files(asm_path)
print("trying to compile asm with GAS")
for i in range(len(asm_to_build)):
    print("compiling with GAS failed trying with NASM")
    exit_code = os.system(f"i686-elf-as -o build/{asm_to_build_no_extensions[i] + ".o"} asm/{asm_to_build[i]}")
    if exit_code != 0:
        exit_code = os.system(f"nasm -f elf32 asm/{asm_to_build[i]} -o build/{asm_to_build_no_extensions[i] + ".o"}")
        if exit_code != 0:
            quit()    


for i in range(len(files_to_build)):
    exit_code = os.system(f"i686-elf-gcc -c {os.getcwd() + "/src/" + files_to_build[i]}  -o {"build/"+files_to_build_no_extensions[i]+".o"} -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude")
    if exit_code != 0:
        quit()
print("system built")

built_files = os.getcwd()+"/build"
files_to_link = [os.path.join(built_files, f) for f in os.listdir(built_files) if os.path.isfile(os.path.join(built_files, f))]
link = ' '.join([item for item in files_to_link])
exit_code = os.system(f"i686-elf-gcc -T linker.ld -o build/Azbest_OS.bin -ffreestanding -O2 -nostdlib {link} -lgcc")
if(exit_code != 0):
    quit()
print("system linked")

if args.nogrub:
    if platform.system() == "Windows":
        exit_code = os.system(f"move build/Azbest_OS.bin {os.getcwd()}")
    else:
        exit_code = os.system(f"mv build/Azbest_OS.bin {os.getcwd()}")
    if args.boot:
        os.system("qemu-system-x86_64 --kernel Azbest_OS.bin")
else:
    if platform.system() == "Windows":
        print("you can't use grub-mkrescue on windows add -g flag.")
        quit()
    exit_code = os.system("mv build/Azbest_OS.bin iso/boot")
    if(exit_code != 0):
        quit()
    
    print("running grub-mkrescue")
    exit_code = os.system("grub-mkrescue -o Azbest_OS.iso iso")
    if(exit_code != 0):
        print("if you are not on linux or mac use -g flag")
        quit()
    if args.boot:
        os.system("qemu-system-x86_64 --cdrom Azbest_OS.iso")

if platform.system() == "Windows":
    exit_code = os.system(f"del {link}")
else:
    exit_code = os.system(f"rm {link}")

if(exit_code != 0):
    quit()
