#include <kernel/mm.h>
#include <stddef.h>
#include <stdint.h>

// Extremely simple heap allocator for bootstrap
static uint8_t heap[1024 * 1024]; // 1MB heap
static size_t heap_ptr = 0;

void* malloc(size_t size) {
    if (heap_ptr + size > sizeof(heap)) return NULL;
    void* ptr = &heap[heap_ptr];
    heap_ptr += size;
    return ptr;
}

void free(void* ptr) {
    // Basic allocator doesn't support free
    (void)ptr;
}
