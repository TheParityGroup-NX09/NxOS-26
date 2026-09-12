/* Tell the linker that the CPU execution starts at the _start label */
ENTRY(_start)

SECTIONS
/* Begin putting code at 1 Megabyte, the standard load address for kernels */
. = 1M;

{
    /* 1. The Multiboot header MUST go at the very front of the file */
    .text : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }

    /* 2. Read-only data (like text strings) */
    .rodata : ALIGN(4K)
    {
        *(.rodata)
    }

    /* 3. Initialized data (like global variables) */
    .data : ALIGN(4K)
    {
        *(.data)
    }

    /* 4. Uninitialized data (like our stack) */
    .bss : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
}
