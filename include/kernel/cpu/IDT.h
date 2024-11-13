#ifndef IDT_H
#define IDT_H

#include "kernel/kernel.h"

// IDT entry structure
struct idt_entry {
    uint16_t base_low;
    uint16_t selector;
    uint8_t  always0;
    uint8_t  flags;
    uint16_t base_high;
};

// IDT pointer structure
struct idt_ptr {
    uint16_t limit;
    uint32_t base;
};

extern struct idt_entry idt[256];
extern struct idt_ptr idtp;

void idt_install();
void idt_set_gate(int num, uint32_t base, uint16_t selector, uint8_t flags);

#endif
