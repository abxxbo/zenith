# zenith
A small, experimental AArch kernel targetting the QEMU Virt Board

## Compilation
Compilation requirements:
- arm-none-eabi-binutils
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
- [ ] Proper UART driver
- [ ] Some form of interrupt handling