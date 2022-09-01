# Makefile Arguments
In the makefile you may see stuff like
```make
$(COMPILER)
```

This is for compability reasons. It allows users to be able to
use more than just one compiler. For example, `aarch64-elf-gcc`
is not packaged in the Ubuntu repositories (at least to my knowledge).

Therefore, the `TARGET` variable can be set for whatever target (`aarch64-elf-gcc`,
`aarch64-gnu-none-gcc`, etc.)

# List of Variables That can be Changed

## The TARGET variable
This is whatever ABI to target.

**Default:** `elf`

## The COMPILER variable
This can be changed to whatever C compiler you'd like, however you'd probably
need to modify the source code.

**Default:** `gcc`