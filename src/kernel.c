#include "../include/terminal.h"
#include "../include/keyboard.h"
#include "../include/stdlib/stdlib.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
/* Check if the compiler thinks you are targeting the wrong operating system. */


static inline void outw(uint16_t port, uint16_t val) {
    __asm__ volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
}
static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void init(){
    terminal_initialize();
    terminal_setcolor(11);
    terminal_writestring("Welcome to Azbest OS! ver:"OS_VERSION". No rights reserved hehe\n");
    terminal_setcolor(10);   
    terminal_writestring("> ");
}

void kernel_main(void) 
{
    init();
	
    char input[256];



	while(1){
		keyboard_handler();
	}
}