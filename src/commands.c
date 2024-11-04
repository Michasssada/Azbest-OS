#include "../include/keyboard.h"
#include "../include/terminal.h"
#include "../include/stdlib.h"
#include "../include/commands.h"
#include <stddef.h>
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
char input[256];
int user_input_color = VGA_COLOR_LIGHT_GREEN;
int error_output_color = VGA_COLOR_RED;
int sys_output_color = VGA_COLOR_WHITE;
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
       int color = toInt(input[11]);
       if(color = 0){
        user_input_color = VGA_COLOR_LIGHT_GREEN;
        terminal_setcolor(VGA_COLOR_LIGHT_GREEN);
       }else if(color = 1){
        user_input_color = VGA_COLOR_GREEN;
        terminal_setcolor(VGA_COLOR_GREEN);
       }
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
        terminal_setcolor(error_output_color);
        terminal_writestring("no such command. enter help for more info");
        terminal_setcolor(user_input_color);
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
