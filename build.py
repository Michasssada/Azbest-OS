import os

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
for i in range(len(files_to_build)):
    exit_code = os.system(f"i686-elf-gcc -c {os.getcwd() + "/src/" + files_to_build[i]}  -o {"build/"+files_to_build_no_extensions[i]+".o"} -std=gnu99 -ffreestanding -O2 -Wall -Wextra -L/include")
    if exit_code != 0:
        quit()
print("system built")
built_files = os.getcwd()+"/src"
file_names = [f for f in os.listdir(directory_path) if os.path.isfile(os.path.join(directory_path, f))]
exit_code = os.system(f"i686-elf-gcc -T linker.ld -o build/Azbest_OS.bin -ffreestanding -O2 -nostdlib asm/boot.o {}  -lgcc -L/include")