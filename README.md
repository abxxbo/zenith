# zenith
A small, experimental AArch kernel targetting the QEMU Virt Board

## Compilation
Compilation requirements:
- Any target of AArch64 binutils. (elf, gnu-eabi, none, etc.)
- qemu

To compile, just run:
```
make
```

To run, do 
```
make run
```

# Goals / Roadmap

## Ground Zero
- [X] Proper UART driver
- [ ] A little MM
	- [X] `free()`
	- [X] `malloc()`
	- [ ] `calloc()`
	- [ ] `realloc()`
- [ ] Some form of interrupt handling