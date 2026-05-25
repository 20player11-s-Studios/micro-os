#ifndef MULTITASKING_H
#define MULTITASKING_H

#include <stdint.h>

typedef struct {
    uint64_t rsp;
    uint64_t cr3;
    uint32_t pid;
    uint32_t state;
} thread_t;

void multitasking_init(void);
void schedule(void);

#endif
