#pragma once

#include <stdint.h>
#include <stddef.h>

#include <mem/heap.h>

void memcpy(void* destination, void* source, uint32_t num);


/* These do not have comments to document
 * what they do. You can just read mem/heap.h */
uint32_t malloc(int size);
void 	   free(void* ptr);
void*    calloc(int size);
void*    realloc(void* ptr, int size);