#include "libc/stdlib.h"

uint64_t malloc(uint64_t size){ return __mem_malloc(size);   }
void   free(uint64_t location){ return __mem_free(location); }
