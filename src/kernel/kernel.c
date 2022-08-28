#include "libc/stdio.h"
#include "hal/mmio.h"

#include "arch/int.h"
#include "mem/heap.h"
 
void kmain(void) {
  puts("Hello world!\r\n");

	uint32_t mmio_addr = get_mmio_base();
	if(mmio_addr == OTHER_ADDR){
		puts("\r\nNon RPi Board Detected.");
	}

	printf("\r\nMMIO base is at: %x\n\r\n", mmio_addr);


	int foo = malloc(1); // allocate one byte
	printf("Allocated 1 byte to 0x%x.\r\n", foo);
	*(int*)foo = 0xf; // set to 15

	int* _ptr = foo;
	int val = *_ptr;
	printf("Checking 0x%x. Expected: 15. Result: %d\r\n", foo, val);

	free(foo);

	// finished initializing, let user do stuff
	printf("%sZenith is done initializing itself...%s\r\n",
					COLOR_Yellow, COLOR_None);
}