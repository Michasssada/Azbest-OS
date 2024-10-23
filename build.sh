i686-elf-gcc -c src/terminal.c  -o terminal.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -L/include
i686-elf-gcc -c src/keyboard.c  -o keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -L/include
i686-elf-gcc -c src/kernel.c  -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -L/include   
i686-elf-gcc -c src/stdlib.c  -o stdlib.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -L/include
i686-elf-gcc -c src/commands.c  -o commands.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -L/include
echo "kernel built"
i686-elf-gcc -T linker.ld -o Azbest_OS.bin -ffreestanding -O2 -nostdlib asm/boot.o terminal.o keyboard.o stdlib.o kernel.o commands.o  -lgcc -L/include
echo "kernel linked"
cp Azbest_OS.bin iso/boot
grub-mkrescue -o build/azbest.iso iso
rm terminal.o keyboard.o kernel.o stdlib.o commands.o 

