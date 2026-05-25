#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/mm.h>
#include <kernel/multitasking.h>
#include <kernel/shell.h>

void kernel_main(unsigned long magic, unsigned long addr) {
    tty_init();
    tty_printf("MicroOS Kernel Loading...\n");

    // Stubbing for now to allow compilation
    tty_printf("GDT/IDT/MM/Multitasking initialization stubs called.\n");

    tty_printf("Welcome to MicroOS!\n");

    shell_start();

    while (1) {
        asm volatile("hlt");
    }
}
