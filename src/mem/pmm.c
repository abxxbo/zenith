/* Zenith source code: pmm.c
 * ==> This is a basic PMM I wrote in a few days
 *     for Zenith. However there's still some problems
 *     (at least for me)
 * 
 * Problems:
 *  - __mem_malloc() does not make a new block with the size
 *    of N, where N is the amount of bytes allocated. */

#pragma once

#include "mem/pmm.h"

block_t blocks[MAX_BLOCKS];

void add_to_blocks(uint64_t starting_addr,
                   uint64_t ending_addr,
                   int free,
                   uint8_t index){
  block_t cblock = {
    .start_addr = starting_addr,
    .end_addr   = ending_addr,
    .freed      = free,
    .length     = (starting_addr)-(ending_addr)
  };

  blocks[index] = cblock;
}


uint64_t block_arr_size = (sizeof(blocks)/sizeof(blocks[0]));

uint64_t find_hole_in_mm(uint64_t n){
  // Loop through each block found in the blocks array
  for(int i = 0; i != block_arr_size; i++){
    if(blocks[i].freed != FREE_BLOCK) continue;
    else {
      // Block is free, check size.
      if(blocks[i].length >= n) return blocks[i].start_addr;
      else return NO_LOC;
    }
  }
}

uint64_t __mem_malloc(uint64_t size){
  // Step 1: get memory hole
  uint64_t m_loc = find_hole_in_mm(size);
  if(m_loc == NO_LOC) return NO_LOC;

  printf("--> Block at addr 0x%x is allocated\n", m_loc);
  // Step 2: Set block to occupied
  
  uint64_t loc = 0;
  for(int i = 0; i != block_arr_size; i++){
    // Step 2a: Loop through each block and find the block
    //          which has the starting address equal to
    //          m_loc
    if(blocks[i].start_addr != m_loc) continue;
    else {
      loc = i;
      break;
    }
  }

  // set block
  blocks[loc].freed = OCCUPIED_BLK;
  return blocks[loc].start_addr;  
}


void __mem_free(uint64_t location){
  #ifndef SEC_F // If SEC_F is not defined
                // show a warning message
                // that you should use free()
                // instead
    printf("WARN: Do not use __mem_free(). Instead, use free()\n");
  #endif
  uint64_t z = 0; // block # to free 
  for(size_t i = 0; i != block_arr_size; i++){
    if(blocks[i].start_addr == location) z = i; break;
  }

  // Block located!! set to free, we can allocate to this!
  blocks[z].freed = FREE_BLOCK;
}

uint64_t __mem_realloc(void* ptr, uint64_t size){
  if(size == 0){
		__mem_free(ptr);
		return NULL;
	}
	// act like malloc()
	if(ptr == 0) return __mem_malloc(size);


	// if none of these cases, reallocate
	// credit: Bonfra from the OSDev Discord
	void* new_ptr = malloc(size);
	if(new_ptr != NULL){
		memcpy(new_ptr, ptr, size);
		free(ptr);
	}
  return new_ptr;
}

uint64_t __mem_calloc(int size){
	void* alloc_mm = __mem_malloc(size); // allocate the block

	// set the memory value to 0
	memcpy(alloc_mm, 0, size);
	return alloc_mm;
}