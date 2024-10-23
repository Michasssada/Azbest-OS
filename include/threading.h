#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <stdint.h>

#define MAX_TASKS 5
#define STACK_SIZE 256

typedef void (*TaskFunc)(void);

// Task control block
typedef struct {
    TaskFunc function;
    uint8_t stack[STACK_SIZE];
    uint8_t isActive;
} Task;

// Function declarations
void yield();
void scheduler();
void create_task(TaskFunc func);

#endif // TASK_MANAGER_H
