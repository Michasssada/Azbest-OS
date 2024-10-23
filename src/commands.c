#include "../include/keyboard.h"
#include "../include/terminal.h"
#include "../include/stdlib.h"
#include "../include/commands.h"
#include <stddef.h>

char input[256];
char commands[10][10] = {
        "sys data. get OS and computer data \n",
        "clear clears screen`",
        "String3",
        "String4",
        "String5"
};

void check_command(){
    getInput(input);
    if(strcmp(input,"sys data")==0){
        azbest_data();
        
        
    }else if(strcmp(input,"help")==0){
        help();
    }
    else if(strcmp(input,"clear")==0){
        clearScreen();
    }
    else
    {
        terminal_setcolor(4);
        terminal_writestring("no such command. enter help for more info");
        terminal_setcolor(10);
    }
}
void azbest_data(){

    char ram[21];
    sysPrint("Azbest OS ");
    sysPrint(OS_VERSION);
    sysPrint("\n");

}
void help(){
    sysPrint("clear - clears the screen\n");
    sysPrint("sys data - prints data about OS.\n");
     
}