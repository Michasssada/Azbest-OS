#include "stdint.h"
void init_heap();
void kernel_main(void);
void panic(char* info);
void gdt_install();
void idt_install();
void enable_interrupts();