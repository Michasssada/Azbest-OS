#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "../include/keyboard.h"
#include "../include/terminal.h"
#include "../include/stdlib.h"
#include "../include/commands.h"
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
char input_char[256];
static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}
size_t input_len = 0;              // Current length of the input
/* Keyboard scancode mapping (partial, for simplicity) */
void clear_buffer(){
    input_len = 0;
    for (size_t i = 0; i < strlen(input_char); i++) {
        input_char[i] = '\0'; // Set each character to null
    }
    terminal_writestring("\n");  
}

static inline void outw(uint16_t port, uint16_t val) {
    __asm__ volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
}
static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}
void append_char(char* str, char c, size_t* len, size_t max_len) {
    if (*len + 1 < max_len) {
        str[*len] = c;      // Add the new character at the end
        (*len)++;           // Update the length of the string
        str[*len] = '\0';   // Add the null-terminator
    }
}

static const char scancode_to_char[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',    /* 0x00 - 0x09 */
    '9', '0', '-', '=', '\b', /* Backspace */
    '\t', /* Tab */
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0,    /* Control key */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0,    /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    0,    /* Right shift */
    '*',
    0,    /* Alt */
    ' ',  /* Space bar */
    0,    /* Caps lock */
    /* F1 - F12 keys not mapped here for simplicity */
};
void remove_last_char(char* str, size_t* len) {
    if (*len > 0) {
        (*len)--;  // Decrease the length
        str[*len] = '\0';  // Null-terminate after removal
    }
}
void handle_keypress(char c) {
	if (c == '\n') {  // Check if the Enter key was pressed
        // Process the input stored in input_buffer (e.g., print it)
        terminal_writestring("\n");  
        check_command();
        clear_buffer();         // New line after the input
        input_len = 0;  // Reset input length for new input
        return;  // Don't add the newline character to the buffer
    }else if (c == '\b') {  // Backspace
        if (input_len > 0) {
            remove_last_char(input_char, &input_len);  // Remove last character from input buffer
            
            // Update terminal position
            if (terminal_column > 0) {
                terminal_column--;
            } else if (terminal_row > 0) {
                terminal_row--;
                terminal_column = VGA_WIDTH - 1;
            }

            // Clear the character on the screen by overwriting with a space
            terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
        }
        return;
    }

    append_char(input_char, c, &input_len, 256);
    terminal_putchar(c);  // Display the key on the screen

}
void myStrCopy(char *destination, const char *source) {
    while (*source) {         // While we haven't reached the end of the source string
        *destination++ = *source++; // Copy each character
    }
    *destination = '\0';     // Null-terminate the destination string
}

void getInput(char *output){
    myStrCopy(output,input_char);

}

void keyboard_handler(void) {
    uint8_t scancode = inb(0x60);
    
    if (scancode < sizeof(scancode_to_char)) {
        char key = scancode_to_char[scancode];
        if (key) {
            handle_keypress(key);  // Handle the keypress by storing the char and displaying it
        }
    }
	delay(400000);
}


/* Interrupt Service Routine for keyboard */
void keyboard_isr(void) {
    keyboard_handler();
    
    // Send End of Interrupt (EOI) signal to PIC
    outb(0x20, 0x20);
}