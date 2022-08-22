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

void printf(char* fmt, ...){
  va_list ap;
	va_start(ap, fmt);

	char* ptr;

	for (ptr = fmt; *ptr != '\0'; ++ptr) {
		if (*ptr == '%') {
			++ptr;
      switch(*ptr){
        case 's':
          puts(va_arg(ap, char*));
          break;
        
        case 'd':
          puts(itoa(va_arg(ap, int), 10));
          break;
        
        case 'x':
          puts("0x");
          puts(itoa(va_arg(ap, uint32_t), 16));
          break;
      }
    } else {
      putc(*ptr);
    }
  }
}