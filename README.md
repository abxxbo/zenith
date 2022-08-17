# zenith
A small, experimental ARMv7 kernel targetting the Cortex A15 development board

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