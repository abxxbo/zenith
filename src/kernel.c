#include <stdint.h>
#include <stddef.h>
#include <limine.h>

#include "libc/stdio.h"
 
#define done() for(;;) __asm__("1: b .");
 
// The following will be our kernel's entry point.
void _start(void) {
    puts("Hello, AArch64 World!");
    // We're done, just hang...
    done();
}