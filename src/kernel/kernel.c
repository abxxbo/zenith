#define UART_ADDR 0x1c090000 // send to uart

void start(){
	*(volatile char*)(UART_ADDR) = 0x61;
}