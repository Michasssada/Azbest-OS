#include "io/terminal.h"
#include "io/keyboard.h"
#include "kernel/kernel.h"
#include "kernel/cpu/GDT.h"
#include "kernel/cpu/idt.h"
#include "defines.h"
#include "stdlib/stdlib.h"
#include "kernel/devices/timer.h"


void kernel_main() 
{
    terminal_initialize();
    initGdt();
    terminal_writestring("Gdt initialized\n");
    initIdt();
    terminal_writestring("interrupts initialized\n");
    initTimer();
    terminal_setcolor(11);
    terminal_writestring("Welcome to Azbest OS! ver:"OS_VERSION". No rights reserved hehe\n");
    terminal_setcolor(10);
    terminal_writestring("> ");
    initKeyboard();
	while(1){
	}
}