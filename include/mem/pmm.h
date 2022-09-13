#pragma once

#include <stddef.h>
#include <stdint.h>

enum BLOCK_FREE {
  FREE_BLOCK   = 1,
  OCCUPIED_BLK = 0
};

typedef struct block {
  uint64_t start_addr;
  uint64_t end_addr;
  uint64_t length;      // end_addr - start_addr, calculated by code
  uint8_t  freed;
} block_t;

#define MAX_BLOCKS 256
#define NO_LOC     0xfafafa

// Add one value to the blocks at index
void add_to_blocks(uint64_t starting_addr, 
                   uint64_t ending_addr,
                   int free, uint8_t index);

// Find the closest place in the memory map
// that can fit N bytes.
uint64_t find_hole_in_mm(uint64_t n);

// Memory allocation functions
// Wrappers in libc/stdlib.h
uint64_t __mem_malloc(uint64_t size);
void     __mem_free(uint64_t location);