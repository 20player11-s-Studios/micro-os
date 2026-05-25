ENTRY(start)

SECTIONS
{
    /* The kernel starts at 1MB */
    . = 1M;

    .text :
    {
        /* Ensure multiboot header is at the beginning */
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
