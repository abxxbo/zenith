/* NOTES: This will break if we are looking for
 * any memory address past END_SEARCH_LOC. This
 * is because this uses 32-bit numbers. This will
 * change in the future.
*/
#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <libc/stdio.h>
#include <libc/stdlib.h>


// The memory-mapped peripherals are where stuff like the UART controller
// is. Zenith's MM will not search here.
#define M_PER_START 0x00000000
#define M_PER_END   0x3FFFFFFF

// The MM will not search this area for free memory, since this
// is reserved for the bootloader.
#define RESERVED_BOOT_START 0x40000000
#define RESERVED_BOOT_END   0x4007FFFF

// The kernel location. Do not search anything before here.
#define KERNEL_LOC 					0x40080000 // This may change in the near future.
																			 // If it does change, linker.ld will
																			 // contain its new value.

extern uint32_t end; // end of the kernel

typedef struct {
	uint32_t start_addr; // starting address of memory
	uint32_t end_addr;	 // ending address of memory
	bool  	 freed;			 // is the memory freed?
} block_t;

// find the closest spot of free memory
uint32_t find_closest_free();

// this allocates size, in bytes and returns
// the starting address
uint32_t __mem_malloc(int size); // allocate "size"
void 		 __mem_free(void* ptr);  // free said allocated area
void* 	 __mem_calloc(int size); // call malloc and set that memory to zero

/* A note to whoever is reading this:
 * I append "__mem" to all the functions here, so that,
 * in stdlib.h, I can easily just do something like
 * uint32_t malloc(int size){ __mem_malloc(size); }.
 * 
 * This is because I want to stay true to how GLIBC does it
 * (malloc/calloc/free are in stdlib.h)
*/