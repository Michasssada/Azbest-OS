//#include "ioterminal.h"
#include "kernel/kernel.h"

// Panic handler
void panic(char* info) {
    terminal_initialize();               // Initialize the terminal
    terminal_setcolor(4);                // Set text color to red (error color)
    terminal_writestring("Kernel Panic"); // Display the "Kernel Panic" message
    
    terminal_setcolor(7);                // Set text color to white
    terminal_writestring("Triggered by "); // Display "Triggered by"
    terminal_writestring(info);          // Display the error info, e.g. "division by zero"
    
    terminal_setcolor(11);               // Set text color to yellow
    terminal_writestring(" Reboot your PC!"); // Suggest to reboot the system
    
    terminal_setcolor(15);               // Restore default text color (white)
    asm("hlt");                          // Halt the processor (stop the system)
}
