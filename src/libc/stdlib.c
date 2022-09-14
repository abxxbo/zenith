#include "libc/stdlib.h"

uint64_t malloc(uint64_t size){
  #ifndef SC_M
    #define SC_M 1234 // doesnt matter
    return __mem_malloc(size, SC_M);
  #endif
}
void   free(uint64_t location){ return __mem_free(location); }
