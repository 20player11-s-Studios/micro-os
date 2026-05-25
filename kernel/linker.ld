ENTRY(start)

SECTIONS
{
    /* The kernel starts at 1MB */
    . = 1M;

    .text :
    {
        /* Ensure multiboot headers are at the very beginning */
        KEEP(*(.multiboot_v1))
        KEEP(*(.multiboot_header))
        *(.text)
    }

    .rodata :
    {
        *(.rodata)
    }

    .data :
    {
        *(.data)
    }

    .bss :
    {
        *(COMMON)
        *(.bss)
    }
}
