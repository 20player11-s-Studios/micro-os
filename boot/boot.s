# Multiboot 1 header (for QEMU -kernel compatibility)
.section .multiboot_v1
.align 4
.long 0x1BADB002
.long 0x00000003
.long -(0x1BADB002 + 0x00000003)

# Multiboot 2 header
.section .multiboot_header
.align 8
header_start:
    .long 0xe85250d6                # magic number (multiboot 2)
    .long 0                         # architecture 0 (protected mode i386)
    .long header_end - header_start # header length
    # checksum
    .long 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    # end tag
    .short 0
    .short 0
    .long 8
header_end:

.section .text
.code32
.global start
start:
    cli
    mov $stack_top, %esp

    # 1. Set up Paging
    call setup_paging
    call enable_paging

    # 2. Load 64-bit GDT
    lgdt gdt64_ptr

    # 3. Jump to Long Mode
    push $0x08
    push $long_mode_start
    lret

setup_paging:
    mov $p3_table, %eax
    or $0b11, %eax
    mov %eax, p4_table

    mov $p2_table, %eax
    or $0b11, %eax
    mov %eax, p3_table

    mov $0b10000011, %eax
    mov %eax, p2_table
    ret

enable_paging:
    mov $p4_table, %eax
    mov %eax, %cr3

    mov %cr4, %eax
    or $(1 << 5), %eax
    mov %eax, %cr4

    mov $0xC0000080, %ecx
    rdmsr
    or $(1 << 8), %eax
    wrmsr

    mov %cr0, %eax
    or $(1 << 31), %eax
    mov %eax, %cr0
    ret

.code64
long_mode_start:
    mov $0, %ax
    mov %ax, %ss
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    # Call kernel_main
    # Multiboot 1: Magic is in EAX, Info in EBX
    # Multiboot 2: Magic is in EAX, Info in EBX
    # Note: We use 64-bit registers to pass arguments to kernel_main (System V AMD64 ABI)
    mov %rbx, %rsi # Info structure
    mov %rax, %rdi # Magic number
    call kernel_main

.Lhalt:
    hlt
    jmp .Lhalt

.section .data
.align 4096
p4_table:
    .skip 4096
p3_table:
    .skip 4096
p2_table:
    .skip 4096

gdt64:
    .quad 0 # Null descriptor
    .quad (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53) # Code segment (64-bit)
gdt64_ptr:
    .short . - gdt64 - 1
    .quad gdt64

.section .bss
.align 16
stack_bottom:
    .skip 16384
stack_top:
