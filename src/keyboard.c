#include "terminal.h"
#include <stdint.h>
#include <stdbool.h>

#define KEYBOARD_DATA_PORT 0x60
#define ENTER_KEY_CODE 0x1C
extern bool isEnterPressed;

// Keyboard scan code table for basic US layout
const char scancode_table[128] = { /* ... (fill as in previous example) ... */ };

// Keyboard ISR
void keyboard_isr() {
    uint8_t scancode = inb(KEYBOARD_DATA_PORT);

    if (scancode < 128) {
        if (scancode == ENTER_KEY_CODE) {
            isEnterPressed = true;
            terminal_writestring("\n");
        } else {
            char c = scancode_table[scancode];
            if (c) {
                terminal_putchar(c);
            }
        }
    }
    // End of interrupt signal to PIC
    outb(0x20, 0x20);
}