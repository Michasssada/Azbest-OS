#include <stddef.h>
#include "terminal.h"
#include "stdlib/stdlib.h"
#include "../include/commands.h"
#include "../include/defines.h"
#include "../include/stdlib/stdlib.h"
void keyboard_handler(void);
void append_char(char* str, char c, size_t* len, size_t max_len);
void handle_keypress(char c);
void keyboard_isr(void);
size_t strlen(const char* str);
void getInput(char *output);
void clear_buffer();