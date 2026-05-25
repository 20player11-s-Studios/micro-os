#ifndef MM_H
#define MM_H

#include <stddef.h>

void mm_init(unsigned long addr);
void* malloc(size_t size);
void free(void* ptr);

#endif
