// thread.c
#include <stddef.h>
#include "../include/thread.h"

// Thread stacks
static uint8_t thread_stack[MAX_THREADS][STACK_SIZE];

// Thread control blocks
static TCB threads[MAX_THREADS];

// Current running thread
static TCB *current_thread = NULL;

// Initialize a single thread
void init_single_thread(TCB *thread, void (*start_func)(void)) {
    // Allocate stack and set initial stack pointer
    thread->stack = (uint32_t *)(thread_stack[thread->id] + STACK_SIZE);
    thread->stack_pointer = thread->stack - 1;

    // Set up initial stack frame to simulate a function call
    *--thread->stack_pointer = (uint32_t)start_func; // Initial instruction pointer
    *--thread->stack_pointer = 0x200;                // EFLAGS (set IF flag)
    for (int i = 0; i < 8; i++) {
        *--thread->stack_pointer = 0; // General-purpose registers
    }

    thread->state = THREAD_READY;
}

// Initialize multiple threads
void thread_init(void (*start_funcs[])(void), int num_threads) {
    if (num_threads > MAX_THREADS) num_threads = MAX_THREADS;

    for (int i = 0; i < num_threads; i++) {
        threads[i].id = i;
        init_single_thread(&threads[i], start_funcs[i]);
    }

    // Set up circular list for round-robin scheduling
    for (int i = 0; i < num_threads; i++) {
        threads[i].next = &threads[(i + 1) % num_threads];
    }

    current_thread = &threads[0]; // Start with the first thread
}

// Perform a context switch
void context_switch(TCB *current, TCB *next) {
    asm volatile (
        "mov %%esp, %0\n\t"            // Save current ESP
        "mov %1, %%esp\n\t"            // Load next ESP
        "pushal\n\t"                   // Save all general-purpose registers
        "mov %%esp, %0\n\t"            // Update saved ESP for current thread
        "popal\n\t"                    // Restore general-purpose registers
        "mov %1, %%esp\n\t"            // Restore next thread's stack pointer
        : "=m" (current->stack_pointer)  // Output operand
        : "m" (next->stack_pointer)    // Input operand
    );
}

// Schedule the next thread
static TCB *schedule_next() {
    TCB *next_thread = current_thread->next;
    while (next_thread->state != THREAD_READY) {
        next_thread = next_thread->next;
    }
    return next_thread;
}

// Yield control to the next thread
void thread_yield() {
    TCB *next_thread = schedule_next();
    if (next_thread != current_thread) {
        TCB *prev_thread = current_thread;
        current_thread = next_thread;
        context_switch(prev_thread, next_thread);
    }
}

// Start the threading system and run the first thread
void thread_run() {
    current_thread->state = THREAD_RUNNING;

    asm volatile (
        "mov %0, %%esp\n\t"
        "popal\n\t"
        "ret\n\t"
        :
        : "m"(current_thread->stack_pointer)
    );

    thread_yield(); // Add this to see if it can yield to another thread
}