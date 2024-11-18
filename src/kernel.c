#include "io/terminal.h"
#include "kernel/kernel.h"
#include "kernel/cpu/GDT.h"
#include "kernel/cpu/idt.h"
#include "defines.h"
#include "stdlib/stdlib.h"
#include "kernel/devices/timer.h"
#include "kernel/memory/memory.h"
void kernel_main(uint32_t magic, struct multiboot_info* bootInfo);

void kernel_main(uint32_t magic, struct multiboot_info* bootInfo) 
{
    terminal_initialize();
    initGdt();
    terminal_writestring("Gdt initialized\n");
    initIdt();
    terminal_writestring("interrupts initialized\n");
    initTimer();
    //initMemory(bootInfo);
    terminal_setcolor(11);
    terminal_writestring("Welcome to Azbest OS! ver:"OS_VERSION". No rights reserved hehe\n");
    terminal_setcolor(10);
    terminal_writestring("> ");
    initKeyboard();
	while(1){
	}
}