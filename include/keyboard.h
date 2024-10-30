// keyboard.h
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

// Keyboard data port and IRQ number
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_IRQ 1
#define ENTER_KEY_CODE 0x1C

// Function prototypes
void keyboard_initialize(void);
void keyboard_isr(void);  // Keyboard interrupt service routine

// Key status flags
extern bool isEnterPressed;

#endif // KEYBOARD_H
