#include <stdint.h>

// Define a GDT entry structure
struct gdt_entry {
    uint16_t limit_low;      // The lower 16 bits of the segment limit
    uint16_t base_low;       // The lower 16 bits of the base address
    uint8_t  base_middle;    // The next 8 bits of the base address
    uint8_t  access;         // Access flags
    uint8_t  granularity;    // Granularity flags
    uint8_t  base_high;      // The highest 8 bits of the base address
} __attribute__((packed));

// Define a pointer to the GDT
struct gdt_ptr {
    uint16_t limit;          // The upper 16 bits of all segment limits
    uint32_t base;           // The address of the first gdt_entry
} __attribute__((packed));

// Declare the GDT and GDT pointer globally
struct gdt_entry gdt[3];
struct gdt_ptr gdtp;
