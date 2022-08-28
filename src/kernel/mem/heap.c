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

	int counter = 0;
	for(uint32_t _loc = closest_free_spot; _loc <= (closest_free_spot+size); _loc++){
		int* _ptr = _loc;
		int val = *_ptr;
		if(val == 0) counter++;
	}

	if(counter-1 != size) return 0;

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

void free(void* ptr){
	// find the end address
	uint32_t block_no = 0;
	for(int i = 0; i < 256; i++){
		if(blocks[i].start_addr == *(uint32_t*)ptr) {
			block_no = i;
			break;
		}
	}

	blocks[block_no].freed = true; // we can allocate this!
	printf("\r\nBlock #%d was freed. Values:\r\n\tStarting addr: \t0x%x\r\n\tEnding addr: \t0x%x\r\n",
					block_no, blocks[block_no].start_addr, blocks[block_no].end_addr);
}