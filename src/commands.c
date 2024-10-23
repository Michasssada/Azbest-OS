#include "../include/keyboard.h"
#include "../include/terminal.h"
#include "../include/stdlib.h"
#include "../include/commands.h"
#include "../include/threading.h"
#include <stddef.h>

char input[256];
char commands[10][10] = {
        "sys data. get OS and computer data \n",
        "clear clears screen`",
        "String3",
        "String4",
        "String5"
};
void setColor(){
    sysPrint("colors: VGA_COLOR_BLUE = 1, VGA_COLOR_GREEN = 2, VGA_COLOR_CYAN = 3, VGA_COLOR_LIGHT_GREEN = 4");
    clear_buffer();

    char color[3]; // Buffer to hold user input
    sysPrint("Enter color (1-4): ");
    
    while (!isEnterPressed) {
        getInput(color); // Get user input
    }
    
    // Compare input to set color
    if (strcmp(color, "1") == 0) {
        setColor(1); // Set color to VGA_COLOR_BLUE
    } else if (strcmp(color, "2") == 0) {
        setColor(2); // Set color to VGA_COLOR_GREEN
    } else if (strcmp(color, "3") == 0) {
        setColor(3); // Set color to VGA_COLOR_CYAN
    } else if (strcmp(color, "4") == 0) {
        setColor(10); // Set color to VGA_COLOR_LIGHT_GREEN
    } else {
        sysPrint("No such command");
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
    else if(strcmp(input,"set color")==0){
        //create_task(setColor);
        //scheduler();
        sysPrint("that func isn't implemented");
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
    sysPrint("set color - sets color.\n");
     
}
