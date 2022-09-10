#include <stdint.h>
#include <stddef.h>
#include <limine.h>

#include "libc/stdio.h"
 
#define done() for(;;) __asm__("1: b .");
 
struct limine_memmap_request mm_req = {
  .id = LIMINE_MEMMAP_REQUEST,
  .revision = 1
};


void _start(void) {
  printf("There are %d entries in the memory map.\n", mm_req.response->entry_count);

  for(uint64_t i = 0; i < mm_req.response->entry_count; i++){
    printf("Entry #%d: Base Addr: 0x%x | Length: 0x%x | Type: %d\n",
            i, mm_req.response->entries[i]->base, 
            mm_req.response->entries[i]->length, mm_req.response->entries[i]->type);
  }
  // We're done, just hang...
  done();
}