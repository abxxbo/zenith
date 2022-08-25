AS := aarch64-elf-as
CC := aarch64-elf-gcc
LD := aarch64-elf-ld

CFLAGS := -O2 -g -Wall -Wextra -Iinclude -ffreestanding

override OFILES := $(shell find ./obj/ -type f -name '*.o'|awk '!/stub/') obj/stub.o
OBJS := $(OFILES)


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


QEMU 			 := qemu-system-aarch64
QEMU_FLAGS := -machine virt \
							-cpu cortex-a57 \
							-monitor stdio \
							-m 256m

run: bin/kernel.elf
	$(QEMU) $(QEMU_FLAGS) -kernel $^