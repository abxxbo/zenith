AS := arm-none-eabi-as
CC := arm-none-eabi-gcc
LD := arm-none-eabi-ld

CFLAGS := -O2 -g -Wall -Wextra -pedantic -Iinclude -ffreestanding

OBJS := obj/kernel.o obj/stub.o obj/stdio.o
all: clean zenith
.PHONY: all

clean:
	rm -rf bin *.elf *.o obj


override CFILES := $(shell find ./ -type f -name '*.c')

zenith:
	mkdir -p obj/ bin/
	$(AS) -march=armv7-a -mcpu=cortex-a15 src/stub.s -o obj/stub.o 
	$(foreach file, $(CFILES), $(CC) $(CFLAGS) -c $(file) -o obj/$(basename $(notdir $(file))).o;)

	$(LD) -Tsrc/linker.ld $(OBJS) -o bin/kernel.elf


run: bin/kernel.elf
	qemu-system-arm -M vexpress-a15 -cpu cortex-a15 -kernel $^