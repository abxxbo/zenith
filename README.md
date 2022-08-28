![Banner](res/logo_trans.png)

---

<h1 align="center">Zenith</h1>

<h2 align="center">A small, experimental AArch kernel targetting the QEMU Virt Board</h2>

<br>
<br>

<h1 align="center">Compilation</h1>

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

<h1 align="center"> Goals / Roadmap </h1>

## Ground Zero
- [X] Proper UART driver
- [ ] A little MM
	- [X] `free()`
	- [X] `malloc()`
	- [ ] `calloc()`
	- [ ] `realloc()`
- [ ] Some form of interrupt handling