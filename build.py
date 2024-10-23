# to use the custom file. the custom file still must be in src directory but can be in a folder in src
import os
directory_path = os.getcwd()+"/src"
build_ignore = open("build_ignore.txt", "r")
build_ignore_names = [line.strip() for line in build_ignore]
build_custom = open("build_file_custom.txt", "r")
build_custom_names = [line.strip() for line in build_ignore]
file_names_unfiltred = [os.path.splitext(file)[0] for file in os.listdir(directory_path) if os.path.isfile(os.path.join(directory_path, file))]
file_names = [item for item in file_names_unfiltred if item not in build_ignore_names]
file_names.extend(build_custom_names)
for i in range(len(file_names)):
    print(file_names[i])
    try:
        exit_code = os.system(f"i686-elf-gcc -c {os.getcwd() + "/src/" + file_names[i]+".c"}  -o {"build/"+file_names[i]+".o"} -std=gnu99 -ffreestanding -O2 -Wall -Wextra -L/include")
        if exit_code != 0:
            raise RuntimeError(f"Command failed with exit code {exit_code}")
    except RuntimeError as e:
        print(f"compilation process failded with \n{e}")
    finally:
        print("compilation succeded")

try:
    link_array = [f"{item}.o" for item in file_names]
    link = ' '.join([f"build/{item}" for item in link_array])
    print(f"linking {link}")
    exit_code = os.system(f"i686-elf-gcc -T linker.ld -o build/Azbest_OS.bin -ffreestanding -O2 -nostdlib asm/boot.o {link}  -lgcc -L/include")
    if exit_code != 0:
        raise RuntimeError(f"Command failed with exit code {exit_code}")
    exit_code = os.system("mv build/Azbest_OS.bin iso/boot")
    if exit_code != 0:
        raise RuntimeError(f"Command failed with exit code {exit_code}")
    exit_code = os.system(f"rm {link}")
    if exit_code != 0:
        raise RuntimeError(f"Command failed with exit code {exit_code}")
    exit_code = os.system("grub-mkrescue -o build/Azbest_OS.iso iso")
    if exit_code != 0:
        raise RuntimeError(f"Command failed with exit code {exit_code}")
except RuntimeError as e:
    print(f"failded \n {e}")
finally:
    print("ISO generated successfully")