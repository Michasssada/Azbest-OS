#include "io/terminal.h"
#include "io/keyboard.h"
#include "kernel/kernel.h"
#include "kernel/cpu/GDT.h"
#include "kernel/cpu/idt.h"
#include "defines.h"
#include "stdlib/stdlib.h"
#include "stdlib/stdio.h"
#include "kernel/devices/timer.h"
#include "kernel/memory/multiboot.h"

extern void enter();
void kmain(uint32_t magic, struct multiboot_info* bootInfo);

void kmain(uint32_t magic, struct multiboot_info* bootInfo) 
{
    terminal_initialize();
    initGdt();
    initIdt();
    initTimer();
    uint32_t mod1 = *(uint32_t*)(bootInfo->mods_addr);
    uint32_t physicalAllocStart = (mod1 + 0xFFF) & ~0xFFF;
    initMemory(bootInfo->mem_upper * 1024, physicalAllocStart);
    kmallocInit(0x1000);
    terminal_setcolor(11);
    terminal_writestring("Welcome to Azbest OS! ver:"OS_VERSION". No rights reserved hehe\n");
    terminal_setcolor(10);
    terminal_writestring("> ");
    initKeyboard();
    enter();
    while(1){
	}
}