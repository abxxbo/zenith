#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include <limine.h>

#include "libc/string.h"

#define COLOR_Red    "\033[1;31m"
#define COLOR_Blue   "\033[1;34m"
#define COLOR_Yellow "\033[1;93m"
#define COLOR_Green  "\033[1;32m"
#define COLOR_None   "\033[0m"

// Write a string to FB.
void puts(char* str);

// Print Formatted string
void printf(char* fmt, ...);