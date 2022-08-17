ENTRY(_start)

SECTIONS {
	. = 0x8001000;
	.stub : { obj/stub.o(.text) }
	.text   : { *(.text) }
	.rodata : { *(.rodata) }
	.data   : { *(.data) }
	.bss    : { *(.bss COMMON) }

	STACK_BASE = .;
	. += 0x10000;
	STACK_TOP = .;
}