#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
void terminal_writestring(const char* data);
void terminal_write(const char* data, size_t size);
void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
static inline void outb(uint16_t port, uint8_t value);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(char c);
void terminal_clear();
extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;
extern bool isEnterPressed;