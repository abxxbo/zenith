#include "libc/stdio.h"

volatile uint8_t* uart = (uint8_t* )0x09000000;


void putc(char c) {
	*uart = c;
}

void puts(const char *s) {
	while(*s != '\0') {
		putc(*s);
		s++;
	}
}