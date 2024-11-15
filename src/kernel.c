#include "io/terminal.h"
#include "io/keyboard.h"
#include "kernel/kernel.h"
#include "kernel/cpu/IDT.h"
#include "stdlib/stdlib.h"
#include "defines.h"
#include "sysdata.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "stdlib/string.h"
void init(){
    initGdt();
    init_heap();
    terminal_initialize();
    terminal_setcolor(11);
    if(Sysdata.experimental){
        printf("experimental on");
    }
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