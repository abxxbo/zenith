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
  uint64_t length;      // end_addr - start_addr
  uint8_t  freed;
} block_t;