#include "stdint.h"
#include "kernel/memory/memory.h"
#include "misc/util.h"

uint32_t memNumVPages;
static uint32_t page_frame_min;
static uint32_t page_frame_max;
static uint32_t total_allocated;
#define NUM_PAGE_DIRS 256
#define NUM_PAGE_FRAMES (0x100000000 / 0x1000 / 8) // note: reduced size
uint8_t physical_memory_bitmap[NUM_PAGE_FRAMES / 8]; // todo: dynamically allocate based on available RAM

extern void infiniteLoop();
static uint32_t page_dirs[NUM_PAGE_DIRS][1024] __attribute__((aligned(4096)));
static uint8_t page_dir_used[NUM_PAGE_DIRS];

void pmm_init(uint32_t mem_low, uint32_t mem_high) {
	page_frame_min = CEIL_DIV(mem_low, 0x1000);
	page_frame_max = mem_high / 0x1000;
	total_allocated = 0;

	memset(physical_memory_bitmap, 0, sizeof(physical_memory_bitmap));
}

void initMemory(uint32_t memHigh, uint32_t physicalAllocStart){
    memNumVPages = 0;
    initial_page_dir[0] = 0;

    infiniteLoop();

    invalidate(0);
    initial_page_dir[1023] = ((uint32_t) initial_page_dir - KERNEL_START) | PAGE_FLAG_PRESENT | PAGE_FLAG_WRITE;
    invalidate(0xFFFFF000);

    pmm_init(physicalAllocStart, memHigh);
    memset(page_dirs, 0, 0x1000 * NUM_PAGE_DIRS);
    memset(page_dir_used, 0, NUM_PAGE_DIRS);
}

void invalidate(uint32_t vaddr){
    asm volatile("invlpg %0" :: "m"(vaddr));
}