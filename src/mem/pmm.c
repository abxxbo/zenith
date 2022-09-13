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