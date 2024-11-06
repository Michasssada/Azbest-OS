#include <stdint.h>
#include "../include/stdlib/free.h"
#include "../include/stdlib/malloc.h"
#include "../include/kernel.h"
#define NULL ((void*)0)

#define HEAP_SIZE 1024  // Define the heap size
#define BLOCK_SIZE 32   // Define the block size for memory allocation

// A simple struct to keep track of allocated blocks
typedef struct Block {
    struct Block* next; // Pointer to the next block
} Block;

uint8_t heap[HEAP_SIZE]; // The heap memory pool
Block* freeList = NULL;   // The free list to manage free memory blocks

// Initialize the heap by creating a free list
void init_heap() {
    freeList = (Block*)heap;  // Set the free list to the start of the heap
    freeList->next = NULL;    // No free blocks initially
}

// Simple malloc implementation
void* malloc(size_t size) {
    if (size == 0) return NULL;

    size_t blocksNeeded = (size + BLOCK_SIZE - 1) / BLOCK_SIZE; // Round up to block size
    Block* current = freeList;
    Block* previous = NULL;

    // Search the free list for a sufficiently large block
    while (current != NULL) {
        if (current == (Block*)((uintptr_t)current + size)) {
            // If there's a block of sufficient size, return it
            if (previous == NULL) {
                freeList = current->next;
            } else {
                previous->next = current->next;
            }
            return (void*)(current + 1); // Return memory right after the block header
        }
        previous = current;
        current = current->next;
    }
    return NULL;  // No suitable block found
}

// Simple free implementation
void free(void* ptr) {
    if (ptr == NULL) return;

    // Return the block to the free list
    Block* block = (Block*)ptr - 1;
    block->next = freeList;
    freeList = block;
}