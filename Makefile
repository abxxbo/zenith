# sigh...
AS := aarch64-linux-gnu-as
CC := aarch64-linux-gnu-gcc
LD := aarch64-linux-gnu-ld

CFLAGS := -O2 -g -Wall -Wextra -pedantic -Iinclude -ffreestanding

OBJS := obj/kernel.o obj/stub.o obj/stdio.o obj/mmio.o
all: clean zenith
.PHONY: all

clean:
	rm -rf bin *.elf *.o obj


override CFILES := $(shell find ./ -type f -name '*.c')

zenith:
	mkdir -p obj/ bin/
	$(AS) src/stub.s -o obj/stub.o 
	$(foreach file, $(CFILES), $(CC) $(CFLAGS) -c $(file) -o obj/$(basename $(notdir $(file))).o;)

	$(LD) -Tsrc/linker.ld $(OBJS) -o bin/kernel.elf


run: bin/kernel.elf
	qemu-system-aarch64 -machine virt -cpu cortex-a57 -monitor stdio -kernel $^