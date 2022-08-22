#pragma once

#include <stddef.h>
#include <stdint.h>

extern volatile uint8_t *uart;

void putc(char c);
void puts(const char* s);