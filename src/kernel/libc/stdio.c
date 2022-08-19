#include "libc/stdio.h"

void putc(char c){
  *(volatile char*)(UART_ADDR) = c;
}