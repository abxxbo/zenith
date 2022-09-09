override KERNEL := myos.elf
 
# Convenience macro to reliably declare overridable command variables.
define DEFAULT_VAR =
    ifeq ($(origin $1),default)
        override $(1) := $(2)
    endif
    ifeq ($(origin $1),undefined)
        override $(1) := $(2)
    endif
endef
 
# It is highly recommended to use a custom built cross toolchain to build a kernel.
# We are only using "cc" as a placeholder here. It may work by using
# the host system's toolchain, but this is not guaranteed.
$(eval $(call DEFAULT_VAR,CC,aarch64-linux-gnu-gcc))
CC := aarch64-linux-gnu-gcc
 
# Same thing for "ld" (the linker).
$(eval $(call DEFAULT_VAR,LD,aarch64-linux-gnu-ld))
 
# User controllable CFLAGS.
CFLAGS ?= -g -O2 -pipe -Wall -Wextra
 
# User controllable preprocessor flags. We set none by default.
CPPFLAGS ?=
 
# User controllable nasm flags.
NASMFLAGS ?= -F dwarf -g
 
# User controllable linker flags. We set none by default.
LDFLAGS ?=
 
# Internal C flags that should not be changed by the user.
override CFLAGS +=       \
    -std=c11             \
    -ffreestanding       \
    -fno-stack-protector \
    -fno-stack-check     \
    -fno-lto             \
    -fno-pie             \
    -fno-pic             \
    -mgeneral-regs-only  \
    -MMD                 \
    -Iinclude
 
# Internal linker flags that should not be changed by the user.
override LDFLAGS +=         \
    -nostdlib               \
    -static                 \
    -m aarch64elf           \
    -z max-page-size=0x1000 \
    -T src/linker.ld
 
# Check if the linker supports -no-pie and enable it if it does.
ifeq ($(shell $(LD) --help 2>&1 | grep 'no-pie' >/dev/null 2>&1; echo $$?),0)
    override LDFLAGS += -no-pie
endif
 
# Internal nasm flags that should not be changed by the user.
override NASMFLAGS += \
    -f elf64
 
# Use find to glob all *.c, *.S, and *.asm files in the directory and extract the object names.
override CFILES := $(shell find src -type f -name '*.c')
override ASFILES := $(shell find src -type f -name '*.S')
override NASMFILES := $(shell find src -type f -name '*.asm')
override OBJ := $(CFILES:.c=.o) $(ASFILES:.S=.o) $(NASMFILES:.asm=.o)
override HEADER_DEPS := $(CFILES:.c=.d) $(ASFILES:.S=.d)
 
# Default target.
.PHONY: all
all: $(KERNEL) makeiso
 
# Link rules for the final kernel executable.
$(KERNEL): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $@
 
# Include header dependencies.
-include $(HEADER_DEPS)
 
# Compilation rules for *.c files.
%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
 
# Compilation rules for *.S files.
%.o: %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
 
# Compilation rules for *.asm (nasm) files.
%.o: %.asm
	nasm $(NASMFLAGS) $< -o $@
 
# Remove object files and the final executable.
.PHONY: clean
clean:
	rm -rf $(KERNEL) $(OBJ) $(HEADER_DEPS) image.iso firmware/

makeiso:
	bash ./get-iso.sh


MACHINE := virt
ARGS		:= -cpu cortex-a72 \
					 -m 512m \
					 -bios firmware/OVMF.fd \
					 -monitor stdio \
					 -smp 4 -device ramfb -device qemu-xhci -device usb-kbd

run: clean-objs ovmf-firmware qemu

clean-objs:
	rm -rf $(KERNEL) $(OBJ) $(HEADER_DEPS) limine/ iso_root/ bin/ obj/

ovmf-firmware:
	mkdir -p firmware
	cd firmware && curl -o OVMF-AA64.zip https://efi.akeo.ie/OVMF/OVMF-AA64.zip && unzip OVMF-AA64.zip
	rm firmware/readme.txt &&	rm firmware/OVMF-AA64.zip

qemu:
	qemu-system-aarch64 -M $(MACHINE) $(ARGS) -cdrom image.iso