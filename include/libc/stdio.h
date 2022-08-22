#pragma once

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "libc/string.h"

#define UART_ADDR 0x09000000
extern volatile uint8_t *uart;

void putc(char c);
void puts(const char* s);

void printf(char* fmt, ...);