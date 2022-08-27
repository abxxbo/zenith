#include "mem/heap.h"

uint32_t find_open_spot(size_t sizeof_block){
	// if the block size is less than 0 or equal to 0,
	// return 0x00. malloc should check against this and
	// not mallocate if it is equal
	if(sizeof_block <= 0) return 0x00;

	// this counter will 
	size_t counter = 0;
	int hex_loc = 0;

	for(uint32_t _begin = BEGIN_SEARCH_LOC; _begin <= END_SEARCH_LOC;
			_begin++){
		// loop through _begin to _begin + sizeof_block. however this is
		// probably not a good idea since this might leading to overflow.

		// check this and require fragmentation! this will return 0x01
		if(_begin + sizeof_block < 0x0000000F) return 0x01;

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
		return 0x01;
	}

	printf("%sEmpty space found from %x->%x%s\r\n", COLOR_Green, hex_loc, 
					hex_loc + sizeof_block, COLOR_None);
	return hex_loc; // this is the location of where memory can be
									// allocated.
}