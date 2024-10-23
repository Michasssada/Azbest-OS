#include "../include/terminal.h"
#include "../include/keyboard.h"
#include "../include/stdlib.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
/* Check if the compiler thinks you are targeting the wrong operating system. */


static inline void outw(uint16_t port, uint16_t val) {
    __asm__ volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
}


void shutdown() {
    // QEMU supports shutdown via I/O port 0x604
    outw(0x604, 0x2000);
    
    // If not running in QEMU, the next method can be a fallback
    // Writing to ACPI PM1a control block (port 0xB004 on some systems)
    outw(0xB004, 0x2000); // This is system-specific and may vary

    // You can also use the keyboard controller (older approach)
    // outw(0x604, 0x2000); // For some other systems (e.g., virtual machines)
    
    // Halt the CPU as a last resort
    __asm__ volatile("hlt");
}
/* I/O port commands */



static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void init(){
    terminal_initialize();
    terminal_setcolor(11);
    terminal_writestring("Welcome to Azbest OS! ver:"OS_VERSION"\n");
    terminal_setcolor(10);
}

void kernel_main(void) 
{
    init();	/* Initialize terminal interface */
	
    char input[256];



	while(1){
        keyboard_handler();
		
	}
}