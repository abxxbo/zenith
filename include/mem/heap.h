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


// The memory-mapped peripherals are where stuff like the UART controller
// is. Zenith's MMU will not search here.
#define M_PER_START 0x00000000
#define M_PER_END   0x3FFFFFFF

// The MMU will not search this area for free memory, since this
// is reserved for the bootloader.
#define RESERVED_BOOT_START 0x40000000
#define RESERVED_BOOT_END   0x4007FFFF

// The kernel location. Do not search anything before here.
#define KERNEL_LOC 					0x40080000 // This may change in the near future.
																			 // If it does change, linker.ld will
																			 // contain its new value.

extern uint32_t end; // end of the kernel

typedef struct {
	uint32_t addr;		// the address of the block
	void* cont;				// the contents
	bool free;				// is the block free?
} block_t;

#define BEGIN_SEARCH_LOC (&end)
#define END_SEARCH_LOC   0x7FFFFFFF
// find_open_spot will return the beginning of memory that can fit 
// a 'block'.
// It will search from "end" to 0x7FFFFFFF (also known as END_SEARCH_LOC)
block_t find_open_spot(size_t sizeof_block);


#define SUCCESS_ 0x00
#define FAILURE_ 0xff
// Possibilities for malloc()'s return value:
// 	0xFF -- failure in allocation
//	0x00 -- success in allocation

// this allocates a block of memory.
char malloc(void* block);

bool is_free(block_t block);