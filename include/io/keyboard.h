#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stddef.h>
#include "terminal.h"
#include "stdlib/stdlib.h"
#include "pseudo_terminal/commands.h"
#include "defines.h"
#include "stdlib/stdlib.h"
void append_char(char* str, char c, size_t* len, size_t max_len);
void handle_keypress(char c);
void initKeyboard(void);
size_t strlen(const char* str);
void getInput(char *output);
void clear_buffer();

#endif