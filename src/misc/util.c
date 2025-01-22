#include "stdint.h"
#include "misc/util.h"

void memset(void *dest, char val, uint32_t count){
    char *temp = (char*) dest;
    for (; count != 0; count --){
        *temp++ = val;
    }

}

void outPortB(uint16_t Port, uint8_t Value){
    __asm__ volatile ("outb %1, %0" : : "dN" (Port), "a" (Value));
}