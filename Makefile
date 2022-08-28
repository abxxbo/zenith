# Changeable -- see docs/make_arguments.md
TARGET 		:= elf
COMPILER	:= gcc

AS := aarch64-$(TARGET)-as
CC := aarch64-$(TARGET)-$(COMPILER)
LD := aarch64-$(TARGET)-ld

CFLAGS := -O2 -g -Wall -Wextra -Iinclude -ffreestanding

override OFILES := $(shell find ./obj/ -type f -name '*.o'|awk '!/stub/') obj/stub.o
OBJS := $(OFILES)


all: clean zenith
.PHONY: all

clean:
	rm -rf bin *.elf *.o obj

override CFILES := $(shell find ./ -type f -name '*.c')
override ASMFILES := $(shell find ./ -type f -name '*.asm')

zenith:
	mkdir -p obj/ bin/
	$(AS) src/stub.s -o obj/stub.o 
	$(foreach file, $(CFILES), $(CC) $(CFLAGS) -c $(file) -o obj/$(basename $(notdir $(file))).o;)
	$(foreach file, $(ASMFILES), $(AS) $(file) -o obj/$(basename $(notdir $(file))).o;)

	$(LD) -Tsrc/linker.ld $(OBJS) -o bin/kernel.elf


QEMU 			 := qemu-system-aarch64
QEMU_FLAGS := -machine virt \
							-cpu cortex-a57 \
							-monitor stdio \
							-m 256m
DEBUG_QEMU := $(QEMU_FLAGS) \
							-d int

run: bin/kernel.elf
	$(QEMU) $(QEMU_FLAGS) -kernel $^


# You will have to install this yourself.
# Arch has it in the AUR.
GDB_TARGET := gdb-multiarch

debug: bin/kernel.elf
	$(QEMU) $(QEMU_FLAGS) -S -s -kernel $^ &
	$(GDB_TARGET) -x debug/debug.gdb