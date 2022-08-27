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


	uint32_t* test = (uint32_t*)0xf7f7f7f7;
	printf("\r\nend kernel is at %x\r\n", &end);
	printf("Testing allocator...\r\n");
	find_open_spot(sizeof(test));
}