#include "stdlib/stdlib.h"
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
