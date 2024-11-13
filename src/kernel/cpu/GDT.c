#include "kernel/cpu/GDT.h"
#include "kernel/kernel.h"
// Null descriptor (0x0)
#define GDT_NULL 0

// Code segment descriptor (kernel mode, executable, readable)
#define GDT_CODE 1

// Data segment descriptor (kernel mode, writable)
#define GDT_DATA 2

// Macros to set the limit and base
#define GDT_SET_LIMIT(granularity, limit) (((limit) & 0xFFFF) | ((granularity) << 16))
#define GDT_SET_BASE(base)                (((base) & 0xFFFFFF) | ((base) >> 24))

// Initialize the GDT entries
void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;
    gdt[num].granularity |= granularity & 0xF0;
    gdt[num].access = access;
}

void gdt_install() {
    // Set the GDT pointer
    gdtp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gdtp.base = (uint32_t)&gdt;

    // Set up the GDT entries
    gdt_set_gate(0, 0, 0, 0, 0);                       // Null descriptor
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);         // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);         // Data segment

    // Load the GDT using assembly
    asm volatile("lgdt (%0)" : : "r" (&gdtp));
    
}
