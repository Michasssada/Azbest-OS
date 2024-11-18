#include "io/keyboard.h"
#include "io/terminal.h"
#include "defines.h"
#include "stdlib/stdlib.h"
#include "pseudo_terminal/commands.h"
#include "sysdata.h"
#include "kernel/kernel.h"
#include "kernel/devices/timer.h"
#include <stddef.h>
#include <stdbool.h>
#include "stdlib/stdio.h"

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

// Function to compare the first `HowMany` characters of two strings
bool compareSomeChars(const char *str1, const char *str2, int HowMany) {
    for (int i = 0; i < HowMany; i++) {
        if (str1[i] != str2[i]) {
            return false;
        }
    }
    return true;
}

char* get_command(char *str, char delimiter) {
    char *start = str;
    
    while (*str) {
        if (*str == delimiter) {
            *str = '\0';  // Replace delimiter with null terminator
            break;
        }
        str++;
    }
    return start;  // Return the first token
}

void get_ticks_command(){
    String buffer;
    intToStr(ticks,buffer,10);
    terminal_writestring(buffer);
}
// Function to check user commands
void check_command() {
    getInput(input);
    char *command = get_command(input, ' ');
    if (strcmp(command, "test") == 0){

        
    }
    else {
        terminal_setcolor(error_output_color);
        terminal_writestring("no such command. enter help for more info\n");
        terminal_setcolor(user_input_color);
    }
}
