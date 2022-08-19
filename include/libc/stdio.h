#pragma once
#include <stddef.h>

#define UART_ADDR 0x1c090000 // send to uart

void putc(char c);


// i hate this
#define puts(c) for(size_t i = 0; i < 10; i++){ \
                  putc(c[i]); }
