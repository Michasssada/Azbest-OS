import os
directory_path = os.getcwd()+"/src"

file_names = [os.path.splitext(file)[0] for file in os.listdir(directory_path) if os.path.isfile(os.path.join(directory_path, file))]
for i in range(len(file_names)):
    print(file_names[i])
    try:
        os.system(f"i686-elf-gcc -c {os.getcwd() + "/src/" + file_names[i]+".c"}  -o {file_names[i]+".o"} -std=gnu99 -ffreestanding -O2 -Wall -Wextra -L/include")
    except Exception as e:
        print(f"compilation process failded with \n{e}")
    finally:
        print("compilation succeded")

try:
    link_array = [f"{item}.o" for item in file_names]
    link = ' '.join(link_array)
    print("linking started")
    print(link)
    #os.system(f"i686-elf-gcc -T linker.ld -o Azbest_OS.bin -ffreestanding -O2 -nostdlib asm/boot.o {link_array}  -lgcc -L/include")
except Exception as e:
    print(f"linking failded \n {e}")
finally:
    print("linking succeded")