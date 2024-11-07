#include "../include/keyboard.h"
#include "../include/terminal.h"
#include "../include/defines.h"
#include "../include/stdlib/stdlib.h"
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
void setColor(){
    if(input[11] != "\n"){
       int color = Int(input[11]);
       if(color = 0){
        user_input_color = VGA_COLOR_LIGHT_GREEN;
        terminal_setcolor(VGA_COLOR_LIGHT_GREEN);
       }else if(color = 1){
        user_input_color = VGA_COLOR_GREEN;
        terminal_setcolor(VGA_COLOR_GREEN);
       }
    }
    else{
        printf("color not specified");
    }
    
}
void check_command(){
    getInput(input);
    if(strcmp(input,"azbestfetch")==0){
        azbestFetch();
        
        
    }else if(strcmp(input,"help")==0){
        help();
    }
    else if(strcmp(input,"clear")==0){
        terminal_clear();
    }
    else if(compareSomeChars(input,"set color",9)){
        setColor();
    }
    else if(strcmp(input,"test")==0){
    }
    else
    {
        String testBuffer;
        terminal_setcolor(error_output_color);
        terminal_writestring("no such command. enter help for more info");
        terminal_setcolor(user_input_color);
    }
}
void azbestFetch(){

    char ram[210];
    printf("Azbest OS ");
    printf(OS_VERSION);
    printf("\n");

}
void help(){
    printf("clear - clears the screen\n");
    printf("azbestfetch - prints data about OS. basically azbest os version of neofetch :).\n");
    printf("set color - sets color of user input.\n light green = 0, green = 1");
     
}
