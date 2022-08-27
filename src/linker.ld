ENTRY(_start)
SECTIONS {
    . = 0x40080000;
    .startup . : { obj/stub.o(.text) }
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss COMMON) }
    . = ALIGN(8);
    . += 0x4000; /* 16kB of stack memory */
    stack_top = .;
}