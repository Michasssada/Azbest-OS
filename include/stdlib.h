#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "../include/terminal.h"
#define OS_VERSION "0.0.1 alpha"
int strcmp(const char* str1, const char* str2);
void intToStr(int value, char* buffer, int base);
void sysPrint(char *in);
void clearScreen();
void delay(uint32_t milliseconds);
void StrCpy(char *destination, const char *source);