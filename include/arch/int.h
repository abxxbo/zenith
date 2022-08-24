#pragma once

#include <stddef.h>
#include "libc/stdio.h"

// enable
void enable_IRQ(void);
void enable_FIQ(void);

// disable
void disable_IRQ(void);
void disable_FIQ(void);