KERNEL_SOURCES = \
	src/kernel.c \
	src/panic.c \
	src/sysdata.c \
	src/stdlib/stdio.c \
	src/stdlib/stdlib.c \
	src/pseudo_terminal/commands.c \
	src/misc/util.c \
	src/kernel/cpu/GDT.c \
	src/kernel/cpu/IDT.c \
	src/kernel/devices/timer.c \
	src/kernel/memory/memory.c \

KERNEL_SOURCES_ASM = \
	asm/boot.asm \
	asm/gdtas.asm \
	asm/idtas.asm \

KERNEL_OBJECTS = $(foreach src,$(KERNEL_SOURCES),bin/$(notdir $(src:.c=.o)))
KERNEL_OBJECTS_ASM = $(foreach src,$(KERNEL_SOURCES_ASM),bin/$(notdir $(src:.asm=.o)))

all: bin $(KERNEL_OBJECTS) $(KERNEL_OBJECTS_ASM) kernel.elf

bin:
	mkdir bin

kernel.elf: $(KERNEL_OBJECTS) $(KERNEL_OBJECTS_ASM)
	ld.lld -T link.ld -o $@ $^

bin/%.o: */%.c
	clang --target=i686-elf -Wall -Wextra -m32 -ffreestanding -Iinclude -nostdlib -std=c99 -fno-stack-protector -c $< -o $@

bin/%.o: */*/%.c
	clang --target=i686-elf -Wall -Wextra -m32 -ffreestanding -Iinclude -nostdlib -std=c99 -fno-stack-protector -c $< -o $@

bin/%.o: */*/*/%.c
	clang --target=i686-elf -Wall -Wextra -m32 -ffreestanding -Iinclude -nostdlib -std=c99 -fno-stack-protector -c $< -o $@


bin/%.o: */%.asm
	nasm -f elf32 $< -o $@

clean:
	rm -rf bin kernel.elf

run:
	qemu-system-x86_64 -kernel kernel.elf
