#include "mem/heap.h"

int count = 0; // number in array
block_t blocks[256];

block_t find_open_spot(uint32_t sizeof_block){
	// if failed, this block will be returned.
	block_t failed = { .addr = 0x00, .cont = NULL, .free = true };

	// if the block size is less than 0 or equal to 0,
	// return 0x00. malloc should check against this and
	// not mallocate if it is equal
	if(sizeof_block <= 0) return failed;

	// this counter will 
	size_t counter = 0;
	int hex_loc = 0;

	for(uint32_t _begin = BEGIN_SEARCH_LOC; _begin <= END_SEARCH_LOC;
			_begin++){
		// loop through _begin to _begin + sizeof_block. however this is
		// probably not a good idea since this might leading to overflow.

		// check this and require fragmentation! this will return 0x01
		if(_begin + sizeof_block < 0x0000000F) return failed;

		// if we are still here, we can do the check
		for(uint32_t _loc = _begin; _loc <= (_begin+sizeof_block); _loc++){
			hex_loc = _begin; // this is the beginning of the memory where
												// allocation can be done. it will be returned
												// once everything finishes.

			// thanks stack overflow
			int* _ptr = _loc;
			int val   = *_ptr;
			if(val == 0) counter++;
		}
		// exit out of loop once done with both
		break;
	}

	if(counter < sizeof_block-1){
		printf("\r\n%sFragmentation Needed! (cannot allocate all memory!)%s\r\n",
						COLOR_Green, COLOR_None);
		printf("Counter is %d, while the size is %d\r\n", counter, sizeof_block);
		return failed;
	}

	block_t block = { .addr = hex_loc, .cont = NULL, .free = true};

	printf("%sEmpty space found from %x->%x%s\r\n", COLOR_Green, hex_loc, 
					hex_loc + sizeof_block, COLOR_None);
	return block; // this is the location of where memory can be
									// allocated.
}

// check if a block is free or not
bool is_free(block_t block){
	return block.free ? true : false;
}


char malloc(void* block){
	uint32_t block_size = sizeof(block);
	block_t b = find_open_spot(block_size);

	// check initial conditions
	if(is_free(b) != true || b.addr == 0x00) return FAILURE_;

	// we can now set the memory's value to block's content.
	*(int*)b.addr = block;

	int x = 0;
	
	// assume 8 bytes
	int b_[8];
	int k = 0;
	int j = 0;
	for(int i = 0; i < (int)sizeof(block); i++){
		b_[j] = ((uintptr_t)block >> k & 0xff);
		j++;
		k += 8;
	}

	for(uint32_t i = b.addr; i <= b.addr+block_size; i++){
		// set value
		int* val = (int*)i;
		*val = b_[x];

		// read value and print it out
		printf("Addr 0x%x is now set to 0x%x\r\n", i, *(uint32_t*)i);
		x++;
	}

	// add block to blocks, then set it to be not free
	b.free = false; // used!
	blocks[count] = b;
	count++;

	// say that we've allocated
	printf("\n%sAllocated 0x%x to address 0x%x!%s",
					"\033[1;94m", block, b.addr, COLOR_None);

	// if we get here, then everything went well.
	return SUCCESS_;
}