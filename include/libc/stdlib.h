#pragma once

#include <stddef.h>
#include <stdint.h>
#include "mem/pmm.h"


// Allocate N bytes
uint64_t malloc(uint64_t size);

// Free a block location
void     free(uint64_t location);