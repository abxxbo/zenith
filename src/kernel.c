#include <stdint.h>
#include <stddef.h>
#include <limine.h>

#include "libc/stdio.h"
#include "libc/stdlib.h"

#include "mem/pmm.h"
 
#define done() for(;;) __asm__("1: b .");
 
struct limine_memmap_request mm_req = {
  .id = LIMINE_MEMMAP_REQUEST,
  .revision = 1
};

void _start(void) {
  printf("%sHello, AArch64 World!%s\n",
          COLOR_Red, COLOR_None);
  printf("There are %d entries in the memory map.\n", mm_req.response->entry_count);

  // append each memory map value to the blocks array
  for(uint64_t i = 0; i < mm_req.response->entry_count; i++){
    if(mm_req.response->entries[i]->type == 1){
      add_to_blocks(mm_req.response->entries[i]->base,
                    mm_req.response->entries[i]->length+mm_req.response->entries[i]->base,
                    FREE_BLOCK, i);
    } else {
      add_to_blocks(mm_req.response->entries[i]->base,
                    mm_req.response->entries[i]->length+mm_req.response->entries[i]->base,
                    OCCUPIED_BLK, i);
    }
  }
  printf("finished.\n");

  uint64_t t = malloc(2);
  printf("Allocated to 0x%x, 2 bytes.\n", t);
  // We're done, just hang...
  done();
}