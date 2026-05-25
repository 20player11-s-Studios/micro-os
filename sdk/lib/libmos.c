#include <libmos.h>
#include <stdint.h>

void mos_print(const char* str) {
    // Perform syscall to print
    asm volatile (
        "mov $1, %%rax\n"
        "mov %0, %%rdi\n"
        "syscall"
        : : "r"(str) : "rax", "rdi"
    );
}

void mos_exit(int code) {
    asm volatile (
        "mov $60, %%rax\n"
        "mov %0, %%rdi\n"
        "syscall"
        : : "r"((long)code) : "rax", "rdi"
    );
}
