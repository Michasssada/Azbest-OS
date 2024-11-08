#include "../include/terminal.h"
#include "../include/keyboard.h"
#include "../include/kernel.h"
#include "../include/stdlib/stdlib.h"
#include "../include/defines.h"
#include "../include/IDT.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
/* Check if the compiler thinks you are targeting the wrong operating system. */
#define MULTIBOOT_HEADER_MAGIC  0x1BADB002

/* Multiboot information structure */
typedef struct multiboot_info {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;
    // More fields can be added as per the Multiboot specification
} multiboot_info_t;

/* Declare the kernel entry function that will receive the multiboot magic and information */
extern void kernel_main(uint32_t magic, uint32_t mb_info_addr);

static inline void outw(uint16_t port, uint16_t val) {
    __asm__ volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
}
static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void init(){
    init_idt();
    init_heap();
    terminal_initialize();
    terminal_setcolor(11);
    terminal_writestring("Welcome to Azbest OS! ver:"OS_VERSION". No rights reserved hehe\n");
    terminal_setcolor(10);   
    terminal_writestring("> ");
}

void kernel_main(uint32_t magic, uint32_t mb_info_addr) 
{

    init();
    
    char input[256];
	while(1){
		keyboard_handler();
	}
}