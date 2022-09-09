#include <stdint.h>
#include <stddef.h>
#include <limine.h>

#include "libc/stdio.h"
 
#define done() for(;;) __asm__("1: b .");
 
// The following will be our kernel's entry point.
void _start(void) {
  printf("Printf test!\nStr: %s\"%s\"%s\nInt: %s%d%s\nHex: %s0x%x%s\n",
          COLOR_Blue, "Hi!", COLOR_None,
          COLOR_Blue, 0xf, COLOR_None,
          COLOR_Blue, 0xc0f33, COLOR_None);

  // We're done, just hang...
  done();
}