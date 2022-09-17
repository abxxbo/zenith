#pragma once

#include <stddef.h>
#include <stdint.h>
#include "mem/pmm.h"


void memcpy(void* destination, void* source, uint32_t num);

// Allocate N bytes
uint64_t malloc(uint64_t size);

// Free a block location
void     free(uint64_t location);