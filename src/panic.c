#include "../include/terminal.h"
#include "../include/kernel.h"

// Panic handler
void panic(char* info) {
    terminal_initialize();
    terminal_setcolor(4);
    terminal_writestring("Kernel Panic");
    terminal_setcolor(7);
    terminal_writestring("Trigged by");
    terminal_writestring(info);
    terminal_setcolor(11);
    terminal_writestring("Reboot your pc!");
    terminal_setcolor(15);
    asm("hlt");
}