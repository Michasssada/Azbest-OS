#include <stdint.h>
#include "../include/IDT.h"
// Structure for an IDT entry
struct idt_entry {
    uint16_t base_low;   // Lower 16 bits of the interrupt handler function address
    uint16_t selector;   // Segment selector (usually the kernel code segment)
    uint8_t  always0;    // Unused, always set to 0
    uint8_t  flags;      // Flags, describes the type of interrupt gate
    uint16_t base_high;  // Upper 16 bits of the interrupt handler function address
} __attribute__((packed));

// Pointer to the IDT
struct idt_ptr {
    uint16_t limit;      // Size of the IDT
    uint32_t base;       // Address of the first entry of the IDT
} __attribute__((packed));

// Declare the IDT
struct idt_entry idt[256];

// Declare a pointer to the IDT
struct idt_ptr idtp;
extern void isr_handler();  

// Function to set an IDT entry
void set_idt_gate(int num, uint32_t base, uint16_t selector, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF;         // Lower 16 bits
    idt[num].base_high = (base >> 16) & 0xFFFF; // Upper 16 bits
    idt[num].selector = selector;              // Segment selector
    idt[num].always0 = 0;                      // Always 0
    idt[num].flags = flags;                    // Interrupt gate flags
}
void init_idt() {
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1; // Set the limit (IDT size - 1)
    idtp.base = (uint32_t)&idt; // Set the base address of the IDT

    // Initialize all entries in the IDT to 0 (no handler)
    for (int i = 0; i < 256; i++) {
        set_idt_gate(i, (uint32_t)isr_handler, 0x08, 0x8E);  // 0x08 is the code segment
    }

    // Load the IDT
    asm volatile("lidt %0" : : "m"(idtp));  // Load the IDT pointer into the IDTR
}