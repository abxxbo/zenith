#include "hal/mmio.h"

uint32_t get_mmio_base() {
  uint32_t reg;
  uint32_t mmio_base;

  // Since we are using AARCH64, we can
  // use the mrs instruction

  __asm__ __volatile__("mrs %x0, midr_el1" : "=r"(reg));

  switch ((reg >> 4) & 0xFFF) {
    case RPI1: mmio_base = 0x20000000; break;
    case RPI2: mmio_base = 0x3F000000; break;
    case RPI3: mmio_base = 0x3F000000; break;
    case RPI4: mmio_base = 0xFE000000; break;
    default:   mmio_base = 0x20000000; break;
  }
  
  return mmio_base;
}