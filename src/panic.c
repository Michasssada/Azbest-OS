#include "../include/terminal.h"
#include "../include/kernel.h"

#include <stdbool.h>

void outb(uint16_t port, uint8_t value);
static inline void outb(uint16_t port, uint8_t value) {
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

// Panic handler 
void panic(void) {
    terminal_initialize();
    terminal_setcolor(4);
    terminal_writestring("Kernel Panic");
    terminal_setcolor(15);
    while (true){ asm volatile ("hlt"); }  
}

void reboot(void) {
    outb(0x64, 0xFE);
}