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