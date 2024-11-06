#include "../include/terminal.h"
#include "../include/kernel.h"

#include <stdbool.h>

// Panic handler 
void panic(void) {
    terminal_initialize();
    terminal_setcolor(11);
    terminal_writestring("Kernel Panic");
    while (true){ asm volatile ("hlt"); }  
}