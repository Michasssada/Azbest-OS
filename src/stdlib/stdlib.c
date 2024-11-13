#include "../../include/stdlib/stdlib.h"
#include "pseudo_terminal/commands.h"
int strcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}
void intToStr(int value, char* buffer, int base) {
    // Handle 0 explicitly, as the empty string is not a valid representation
    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';  // Null-terminate the string
        return;
    }

    // Flag for negative numbers
    int isNegative = 0;
    if (value < 0 && base == 10) {
        isNegative = 1;
        value = -value; // Make value positive for further processing
    }

    // Process individual digits
    char temp[32]; // Buffer to hold the digits in reverse order
    int i = 0;
    while (value != 0) {
        int remainder = value % base;
        temp[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0'; // Convert digit to char
        value /= base;
    }

    // Add the negative sign if needed
    if (isNegative) {
        temp[i++] = '-';
    }

    // Reverse the string
    for (int j = 0; j < i; j++) {
        buffer[j] = temp[i - j - 1];
    }
    buffer[i] = '\0'; // Null-terminate the string
}

void printf(char *in){
    terminal_setcolor(15);
    terminal_writestring(in);
    terminal_setcolor(user_input_color);
}
// Function to read the Time Stamp Counter
static inline uint64_t read_tsc() {
    uint32_t lo, hi;
    __asm__ volatile (
        "rdtsc"
        : "=a"(lo), "=d"(hi)
    );
    return ((uint64_t)hi << 32) | lo; // Combine high and low parts
}

#define PIT_BASE 0x43 // PIT Control Register
#define PIT_CHANNEL0 0x40 // Channel 0 Data Port

void pit_init(uint32_t frequency) {
    // Set PIT to the desired frequency
    uint32_t divisor = 1193180 / frequency; // PIT frequency is 1193180 Hz
    outb(PIT_BASE, 0x36); // Set mode: square wave generator
    outb(PIT_CHANNEL0, divisor & 0xFF); // Set low byte
    outb(PIT_CHANNEL0, (divisor >> 8) & 0xFF); // Set high byte
}
static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile (
        "outb %0, %1"
        :
        : "a"(value), "Nd"(port)
    );
}

// Function to read from an I/O port
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile (
        "inb %1, %0"
        : "=a"(ret)
        : "Nd"(port)
    );
    return ret;
}
void delay(uint32_t milliseconds) {
    // Convert milliseconds to frequency ticks
    pit_init(1000); // Set PIT for 1000 Hz (1 tick = 1 ms)
    
    for (uint32_t i = 0; i < milliseconds; i++) {
        // Wait for one tick
        while ((inb(PIT_CHANNEL0) & 0x01) == 0) {
            // Wait until the PIT generates an interrupt
        }
    }
}
void StrCpy(char *destination, const char *source) {
    while (*source) {         // While we haven't reached the end of the source string
        *destination++ = *source++; // Copy each character
    }
    *destination = '\0';     // Null-terminate the destination string
}
int Int(const char *str) {
    int result = 0;
    while (*str) {
        // Check if the character is a digit
        if (*str < '0' || *str > '9') {
            break; // Non-digit character found, stop parsing
        }
        result = result * 10 + (*str - '0');
        str++;
    }
    return result;
}
