#include "kernel/cpu/GDT.h"
#include "misc/util.h"
extern void gdt_flush(uint32_t);
extern void tss_flush();


struct gdt_entry_struct gdt_entries[6];
struct gdt_prt_struct gdt_prt;
struct tss_entry_struct tss_entry;

void initGdt(){
    gdt_prt.limit = (sizeof(struct gdt_entry_struct) * 6) -1;
    gdt_prt.base = (uint32_t)&gdt_entries;
    setGdtGate(0,0,0,0,0);
    setGdtGate(1,0,0xFFFFFFFF,0x9A,0xCF);
    setGdtGate(2,0,0xFFFFFFFF,0x92,0xCF);
    setGdtGate(3, 0, 0xFFFFFFFF, 0x9A, 0xCF);  // User Code Segment (Ring 3)
    setGdtGate(4, 0, 0xFFFFFFFF, 0x92, 0xCF);  // User Data Segment (Ring 3)
    writeTSS(5, 0x10, 0x90000);  // 0x90000 is example stack top
    gdt_flush((uint32_t)&gdt_prt);
    tss_flush();
}
void writeTSS(uint32_t num, uint16_t ss0, uint32_t esp0) {
    uint32_t base = (uint32_t) &tss_entry;
    uint32_t limit = sizeof(tss_entry) - 1;

    setGdtGate(num, base, limit, 0xE9, 0x00);
    memset(&tss_entry, 0, sizeof(tss_entry));

    tss_entry.ss0 = ss0;
    tss_entry.esp0 = esp0;   // 🚀 Make sure this is a VALID KERNEL STACK ADDRESS!

    tss_entry.cs = 0x08 | 0x3;
    tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x10 | 0x3;
}


void setGdtGate(uint32_t num, uint32_t base,uint32_t limit, uint8_t access, uint8_t gran){
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit = (limit & 0xFFFF);
    gdt_entries[num].flags = (limit >> 16) & 0x0F;
    gdt_entries[num].flags |= (gran & 0xF0);

    gdt_entries[num].access = access;

}