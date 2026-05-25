#include <kernel/multitasking.h>
#include <kernel/mm.h>
#include <kernel/tty.h>

static thread_t* current_thread;
static thread_t* threads[16];
static int thread_count = 0;

void multitasking_init(void) {
    tty_printf("Initializing Multitasking...\n");
    // Create initial kernel thread
    thread_t* t = (thread_t*)malloc(sizeof(thread_t));
    t->pid = 0;
    t->state = 1; // Running
    threads[thread_count++] = t;
    current_thread = t;
}

void schedule(void) {
    // Simple round-robin
    int next = (current_thread->pid + 1) % thread_count;
    current_thread = threads[next];
    // Context switch logic would go here
}
