#pragma once

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "libc/string.h"

#define UART_ADDR 0x09000000
extern volatile uint8_t *uart;


#define COLOR_Red    "\033[1;31m"
#define COLOR_Blue   "\033[1;34m"
#define COLOR_Yellow "\033[1;93m"
#define COLOR_Green  "\033[1;32m"
#define COLOR_None   "\033[0m"


void putc(char c);
void puts(const char* s);
void printf(char* fmt, ...);