#include "kernel/cpu/IDT.h"
#include "kernel/kernel.h"

// Declare the IDT and IDT pointer
struct idt_entry idt[256];
struct idt_ptr idtp;

// Macros for flags
#define IDT_INTERRUPT_GATE 0x8E
#define IDT_TRAP_GATE 0x8F

// Set a gate in the IDT
void idt_set_gate(int num, uint32_t base, uint16_t selector, uint8_t flags) {
    idt[num].base_low = (base & 0xFFFF);
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].selector = selector;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

// Install the IDT
void idt_install() {
    // Set the IDT pointer
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (uint32_t)&idt;

    // Clear the IDT
    for (int i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    // Set up the IDT gates (interrupts and exceptions)
    // Example for setting an interrupt handler
    // idt_set_gate(32, (uint32_t)interrupt_handler, 0x08, IDT_INTERRUPT_GATE); // 32 is the IRQ number for timer

    // Load the IDT using assembly
    asm volatile("lidt (%0)" : : "r" (&idtp));
}

