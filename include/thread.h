// thread.h

#ifndef THREAD_H
#define THREAD_H

#include <stdint.h>

// Thread states
#define THREAD_RUNNING 1
#define THREAD_READY 2
#define THREAD_BLOCKED 3

// Stack size and number of threads
#define STACK_SIZE 4096
#define MAX_THREADS 3

// Thread Control Block (TCB) structure
typedef struct TCB {
    uint32_t id;
    uint32_t *stack;
    uint32_t *stack_pointer;
    uint32_t state;
    struct TCB *next;
} TCB;

// Public API functions
void thread_init(void (*start_funcs[])(void), int num_threads);
void thread_yield();
void thread_run();

#endif // THREAD_H
