#include "../include/threading.h"

static Task tasks[MAX_TASKS];
static uint8_t currentTask = 0;  // Current task index

// Function to create a new task
void create_task(TaskFunc func) {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (!tasks[i].isActive) {
            tasks[i].function = func;
            tasks[i].isActive = 1;
            break;
        }
    }
}

// Yield function to switch between tasks
void yield() {
    // Save the current task's stack pointer
    __asm__ volatile (
        "movl %%esp, %0" // Store the current stack pointer
        : "=m"(tasks[currentTask].stack) // Output
    );

    currentTask = (currentTask + 1) % MAX_TASKS; // Switch to the next task

    // Restore the next task's stack pointer
    __asm__ volatile (
        "movl %0, %%esp" // Restore the new stack pointer
        : 
        : "m"(tasks[currentTask].stack) // Input
    );
}

// Scheduler function to run active tasks
void scheduler() {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (tasks[i].isActive) {
            tasks[i].function(); // Call the task function
        }
    }
}