#include "mem/heap.h"


int count = 0;
block_t blocks[256];

uint32_t find_closest_free(){
	for(uint32_t _loc = &end; _loc <= (0x7FFFFFFF); _loc++){
		int* _ptr = _loc;
		int val = *_ptr;
		if(val == 0) return _loc; // return the closest free memory
	}
	// no memory free!
	return 0x00;
}

uint32_t malloc(int size){
	if(size <= 0) return 0;

	uint32_t closest_free_spot = find_closest_free();

	// This is the block we will use to add to the blocks
	// array. It signifies that this block is NOT free
	// and should not be re-allocated.
	block_t block = { .start_addr = closest_free_spot, .freed = false,
										.end_addr   = closest_free_spot+size};

	// append to array
	blocks[count] = block;
	count++;

	return closest_free_spot;
}