#include <kernel/syscall.h>
#include <kernel/tty.h>

void syscall_handler(uint64_t syscall_num, uint64_t arg1) {
    switch (syscall_num) {
        case 1: // print
            tty_puts((const char*)arg1);
            break;
        case 60: // exit
            tty_printf("Process exited with code %d\n", (int)arg1);
            break;
        default:
            tty_printf("Unknown syscall: %d\n", (int)syscall_num);
            break;
    }
}

void syscall_init(void) {
    // In x86_64, use LSTAR MSR to set syscall handler
    // For simplicity, we'll assume the handler is called by an ISR or MSR
}
