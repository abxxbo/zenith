#include "libc/stdio.h"
#include "hal/mmio.h"
 
void kmain(void) {
  puts("Hello world!");

	uint32_t mmio_addr = get_mmio_base();
	if(mmio_addr == OTHER_ADDR){
		puts("\r\nNon RPi Board Detected.");
	}
}