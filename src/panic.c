#include "../include/terminal.h"
#include "../include/kernel.h"

#include <stdbool.h>

// Panic handler 
void panic(void) {
    terminal_initialize();
    terminal_setcolor(4);
    terminal_writestring("Kernel Panic");
    terminal_setcolor(15);
    while (true){ asm volatile ("hlt"); }  
}