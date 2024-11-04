#include "../include/keyboard.h"
#include "../include/terminal.h"
#include "../include/stdlib.h"
#include "../include/commands.h"
#include <stddef.h>

char input[256];

bool compareSomeChars(const char *str1, const char *str2, int HowMany) {
    for (int i = 0; i < HowMany; i++) {
        if (str1[i] != str2[i]) {
            return false; // Characters do not match
        }
    }
    return true; // First five characters match
}
char commands[10][10] = {
        "sys data. get OS and computer data \n",
        "clear clears screen`",
        "String3",
        "String4",
        "String5"
};
void setColor(){
    if(input[11] != "\n"){
        
    }
    else{
        sysPrint("color not specified");
    }
    
}
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
    else if(compareSomeChars(input,"set color",9)){
        setColor();
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
    sysPrint("set color - sets color.function is currently unavailble. it will be availble as soon as posible\n");
     
}
