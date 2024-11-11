# new better build system
import os
import argparse

parser = argparse.ArgumentParser(description="Example of adding custom flags.")
parser.add_argument('-b', '--boot', action='store_true', help="boots the os.")
parser.add_argument('-g', '--nogrub', action='store_true', help="compiles only, doesn't run grub-mkrescue.")
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


directory_path = os.getcwd()+"/src"
files_to_build, files_to_build_no_extensions = get_all_files(directory_path)

exit_code = os.system("i686-elf-as -o build/boot.o asm/boot.s")

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
    exit_code = os.system(f"mv build/Azbest_OS.bin {os.getcwd()}")
    if args.boot:
        os.system("qemu-system-x86_64 --kernel Azbest_OS.bin")
else:
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


exit_code = os.system(f"rm {link}")
if(exit_code != 0):
    quit()
