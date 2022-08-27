#include "libc/stdio.h"

volatile uint8_t* uart = (uint8_t*)UART_ADDR;

void putc(char c) {
	*uart = c;
}

void puts(const char *s) {
	while(*s != '\0') {
		putc(*s);
		s++;
	}
}

// #define 's'  's'
// #define 'd'  'd'
// #define 'h'  'x'
// #define 'c' 'c'

void printf(char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	char* ptr;

	for (ptr = fmt; *ptr != '\0'; ++ptr) {
		if (*ptr == '%') {
			++ptr;
			switch (*ptr) {
				case 's':	// string
					puts(va_arg(ap, char*));
					break;
				case 'd': // integer
					puts(itoa(va_arg(ap, int), 10));
					break;
				case 'x': // hexadecimal
					puts(itoa(va_arg(ap, uint32_t), 16));
					break;
				case 'c':
					// GCC complains that you can't have 'char'
					// as a type for va_arg, so it must be int
					// char r[2] = { va_arg(ap, int), 0 }; // null terminate it
					putc(va_arg(ap, int));
			}
		} else {
			char t[2] = { *ptr, 0 };
			puts(t);
		}
	}
}
