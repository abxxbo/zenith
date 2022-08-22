#pragma once

#include <stddef.h>
#include <stdint.h>


#define UART_ADDR 0x09000000
extern volatile uint8_t *uart;

void putc(char c);
void puts(const char* s);