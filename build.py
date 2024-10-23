import os
directory_path = os.getcwd()+"/src"

file_names = [os.path.splitext(file)[0] for file in os.listdir(directory_path) if os.path.isfile(os.path.join(directory_path, file))]
for i in range(len(file_names)):
    print(file_names[i])
    try:
        exit_code = os.system(f"i686-elf-gcc -c {os.getcwd() + "/src/" + file_names[i]+".c"}  -o {"build/"+file_names[i]+".o"} -std=gnu99 -ffreestanding -O2 -Wall -Wextra -L/include")
        if exit_code != 0:
            raise RuntimeError(f"Command failed with exit code {exit_code}")
    except Exception as e:
        print(f"compilation process failded with \n{e}")
    finally:
        print("compilation succeded")

try:
    link_array = [f"{item}.o" for item in file_names]
    link = ' '.join([f"build/{item}" for item in link_array])
    print(f"linking {link}")
    os.system(f"i686-elf-gcc -T linker.ld -o build/Azbest_OS.bin -ffreestanding -O2 -nostdlib asm/boot.o {link}  -lgcc -L/include")
    os.system("mv build/Azbest_OS.bin iso/boot")
    os.system(f"rm {link}")
    os.system("grub-mkrescue -o build/Azbest_OS.iso iso")
except Exception as e:
    print(f"linking failded \n {e}")
finally:
    print("linking succeded")
