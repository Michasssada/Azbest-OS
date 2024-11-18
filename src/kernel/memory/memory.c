#include "kernel/memory/memory.h"
#include "stdint.h"
#include "stdlib/stdio.h"
void initMemory(struct multiboot_info* bootInfo){
    for (int i = 0; i < bootInfo->mmap_length; i += sizeof(struct multiboot_mmap_entry))
    {
        struct multiboot_mmap_entry *mmmt = (struct multiboot_mmap_entry*)(bootInfo->mmap_addr + i);
        printf("low addr: %x | High Addr: %x | low length: %x | high length: %x | size: %x | type: %d \n", mmmt->addr_low, mmmt->addr_high, mmmt->len_low, mmmt->len_high, mmmt->size, mmmt->type);
    }
    
    
}