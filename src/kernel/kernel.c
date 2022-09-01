#include <libc/stdio.h>
#include <libc/stdlib.h>

#include <hal/mmio.h>
 
void kmain(void) {
  puts("Hello world!\r\n");

	uint32_t mmio_addr = get_mmio_base();
	if(mmio_addr == OTHER_ADDR){
		puts("\r\nNon RPi Board Detected.");
	}

	printf("\r\nMMIO base is at: 0x%x\n\r\n", mmio_addr);

	// finished initializing, let user do stuff
	printf("%sZenith is done initializing itself...%s\r\n",
					COLOR_Yellow, COLOR_None);
}