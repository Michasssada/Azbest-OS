#include "../include/threading.h"

typedef void (*TaskFunc)(void);

// Task control block
typedef struct {
    TaskFunc function;
    uint8_t *stackPointer;
    uint8_t isActive;
} Task;

// Stack for each task
uint8_t taskStacks[MAX_TASKS][STACK_SIZE];

// Global array of tasks
Task tasks[MAX_TASKS];
uint8_t currentTask = 0;  // Current task index

void yield();
void scheduler();

// Function to create a new task
void create_task(TaskFunc func) {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (!tasks[i].isActive) {
            tasks[i].function = func;
            tasks[i].stackPointer = &taskStacks[i][STACK_SIZE - 1]; // Set stack pointer
            tasks[i].isActive = 1;
            break;
        }
    }
}
void yield() {
    // Save current task's stack pointer
    tasks[currentTask].stackPointer = (uint8_t *)__get_MSP(); // Assuming ARM Cortex-M
    currentTask = (currentTask + 1) % MAX_TASKS; // Switch to the next task

    // Restore the next task's stack pointer
    __set_MSP((uint32_t)tasks[currentTask].stackPointer); // Assuming ARM Cortex-M
}

// Scheduler function to run active tasks
void scheduler() {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (tasks[i].isActive) {
            // Restore stack pointer
            __set_MSP((uint32_t)tasks[i].stackPointer); // Assuming ARM Cortex-M
            tasks[i].function(); // Call the task function
        }
    }
}