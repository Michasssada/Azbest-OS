#include "pic.h"
#include <stdint.h>

#define PIC1 0x20         // Master PIC
#define PIC2 0xA0         // Slave PIC
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)
#define PIC_EOI 0x20      // End-of-interrupt command

void pic_remap() {
    outb(PIC1_COMMAND, 0x11); // Initialize PICs
    outb(PIC2_COMMAND, 0x11);
    outb(PIC1_DATA, 0x20);    // Offset PIC1 to 0x20
    outb(PIC2_DATA, 0x28);    // Offset PIC2 to 0x28
    outb(PIC1_DATA, 0x04);    // Tell Master PIC about Slave PIC
    outb(PIC2_DATA, 0x02);    // Tell Slave PIC its cascade identity
    outb(PIC1_DATA, 0x01);    // 8086 mode
    outb(PIC2_DATA, 0x01);
}

void pic_unmask(uint8_t irq) {
    uint16_t port;
    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }
    uint8_t mask = inb(port) & ~(1 << irq);
    outb(port, mask);
}