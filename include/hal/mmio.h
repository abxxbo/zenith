#pragma once

#include <stdint.h>
#include <stddef.h>

#include "libc/stdio.h"

enum RPI_BOARDS {
  RPI1 = 0xb76,
  RPI2 = 0xc07,
  RPI3 = 0xd03,
  RPI4 = 0xd08
};

enum MMIO_ADDR_BOARD {
  RPI1_ADDR   = 0x20000000,
  RPI2_ADDR   = 0x3f000000,
  RPI3_ADDR   = 0x3f000000,
  RPI4_ADDR   = 0xfe000000,
  OTHER_ADDR  = 0x20000000
};


uint32_t get_mmio_base();