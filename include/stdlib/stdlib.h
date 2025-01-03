#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "io/terminal.h"
#include "string.h"
int strcmp(const char* str1, const char* str2);
void intToStr(int value, char* buffer, int base);
void clearScreen();
int Int(const char *str);
void StrCpy(char *destination, const char *source);
static inline void outb(uint16_t port, uint8_t value);
static inline uint8_t inb(uint16_t port);