void initMemory(uint32_t memHigh, uint32_t physicalAllocStart);
void invalidate(uint32_t vaddr);

extern uint32_t initial_page_dir[1024];
#define KERNEL_START         0xC0000000
#define PAGE_FLAG_PRESENT (1 << 0)
#define PAGE_FLAG_WRITE   (1 << 1)