#include <stdint.h>

#define MAX_TASKS 5
#define STACK_SIZE 256
typedef void (*TaskFunc)(void);

void create_task(TaskFunc func);
void scheduler();