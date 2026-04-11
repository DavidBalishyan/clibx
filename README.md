# clibx

A small C utility library with common macros and helper functions designed to simplify everyday C development tasks.

## Overview

- array size calculation (`ARRAY_SIZE`)
- min/max/clamp/absolute operations (`MIN`, `MAX`, `CLAMP`, `ABS`)
- swapping values (`SWAP`)
- safer dynamic allocation (`NEW`, `NEW_ARRAY`, `FREE`)
- logging and error handling (`LOG`, `ERROR`)
- loop helpers (`FOR`, `FOR_RANGE`)
- boolean support when `stdbool.h` is not available (`clibx_bool`, `clibx_true`, `clibx_false`)
- safe string comparison (`STREQ`)
- simple line input (`read_line`)
- array printing helpers for `int`, `double`, and `char`

The `main.c` file contains an example program that demonstates the helper macros and functions.

## Files

- `clibx.h` - header-only utility library
- `main.c` - example program demonstrating `clibx.h`

## Build

Use a standard C compiler such as `gcc`:

```bash
gcc -Wall -Wextra main.c -o main
```

## Run

```bash
./main
```

The example program prints array information, uses utility macros for math and memory, demonstrates loop helpers, and reads one line of input from the user.

## Notes

- `clibx.h` is header-only and does not require separate compilation.
- This project is intended as a starting point for small CLI utilities or as a teaching example for macro-based helpers in C.

