# clibx

A small, header-only C utility library with common macros and helper functions designed to simplify everyday C development tasks.

## Table of Contents

- [Overview](#overview)
- [clibx.h - Main Library](#clibxh---main-library)
- [clibx_print.h - Optional Standalone Printf](#clibx_printh---optional-standalone-printf)
- [Files](#files)
- [Build & Run the demos](#build--run-the-demos)

## Overview

**clibx** provides lightweight, macro-based utilities for common C programming patterns, reducing boilerplate and improving code readability. Everything is header-only with zero dependencies beyond the C standard library.

> **Portability note:** Most of `clibx.h` is standard C11. Features inside the `#ifdef __GNUC__` block (`SWAP`, `LIKELY`, `UNLIKELY`, `DEPRECATED`, `NODISCARD`, `TYPE_NAME`, `TYPE_FUNC`) require GCC or Clang. Safe no-op fallbacks are provided for other compilers.

## clibx.h - Main Library
### Installation 
#### Option 1 - wget or curl
```bash
wget https://raw.githubusercontent.com/DavidBalishyan/clibx/refs/heads/main/clibx.h
```
#### Option 2 - clone the repository
```bash
git clone https://github.com/DavidBalishyan/clibx.git
# Copy the clibx.h file wherever you want
```
---
#### `str`
An alias over char* to improve DX and code readability

### Array Operations

#### `ARRAY_SIZE(arr)`
Compile-time calculation of array element count. Only works with stack-allocated arrays.

```c
int arr[] = {1, 2, 3, 4, 5};
size_t len = ARRAY_SIZE(arr);  // len = 5
print_int_array(arr, len);     // Output: [1, 2, 3, 4, 5]
```

#### Array Printing Helpers
- `print_int_array(arr, len)` - Print integer arrays with comma-separated formatting
- `print_double_array(arr, len)` - Print floating-point arrays
- `print_char_array(arr, len)` - Print character arrays with quotes

---

### Math Operations

#### `MIN(a, b)` / `MAX(a, b)`
Return the smaller or larger of two values (type-agnostic).

```c
int x = MIN(10, 20);    // x = 10
int y = MAX(10, 20);    // y = 20
```

#### `CLAMP(x, min, max)`
Restrict a value within a range.

```c
int clamped = CLAMP(25, 0, 15);  // Result: 15 (capped at max)
int clamped = CLAMP(-5, 0, 15);  // Result: 0 (floored at min)
```

#### `ABS(x)`
Get the absolute value of a number.

```c
int result = ABS(-42);  // result = 42
```

#### `LERP(v0, v1, t)`
Linear interpolation between two values. `t` should be in the range `[0.0, 1.0]`.

```c
double result = LERP(0.0, 100.0, 0.25);  // result = 25.0
```

#### `IS_POWER_OF_2(n)`
Check whether an integer is a power of two. Returns non-zero if true.

```c
IS_POWER_OF_2(8);   // true
IS_POWER_OF_2(6);   // false
```

#### `NEXT_POWER_OF_2(n)`
Return the next power of two strictly greater than `n`. Requires `<math.h>`.

```c
NEXT_POWER_OF_2(5);   // 8
NEXT_POWER_OF_2(8);   // 16
```

---

### Bitwise Operations

#### `BIT(x)`
Returns a 64-bit integer with the `x`-th bit set to 1.

```c
unsigned long long mask = BIT(3); // 8 (0b1000)
```

#### `SET_BIT(val, pos)` / `CLEAR_BIT(val, pos)` / `TOGGLE_BIT(val, pos)`
Modifies the specified bit position in `val` in-place.

```c
int flags = 0;
SET_BIT(flags, 2);    // flags = 4
CLEAR_BIT(flags, 2);  // flags = 0
TOGGLE_BIT(flags, 1); // flags = 2
```

#### `CHECK_BIT(val, pos)`
Returns true (non-zero) if the bit at `pos` is set, and false (0) otherwise.

```c
if (CHECK_BIT(flags, 1)) {
    // Bit 1 is set
}
```

---

### Variable Operations

#### `SWAP(a, b)` *(GCC/Clang only)*
Exchange the values of two variables. Type-safe using `__typeof__`. Falls back to a `memcpy`-based swap on other compilers.

```c
int a = 10, b = 20;
SWAP(a, b);
// Now: a = 20, b = 10
```

---

### Memory Management

#### `NEW(type)`
Allocate memory for a single variable.

```c
int *ptr = NEW(int);
*ptr = 99;
FREE(ptr);
```

#### `NEW_ARRAY(type, count)`
Allocate memory for an array.

```c
int *arr = NEW_ARRAY(int, 100);
FREE(arr);  // Sets arr to NULL after freeing
```

#### `NEW_ZEROED(type)`
Allocate and zero-initialise memory for a single variable using `calloc`.

```c
int *ptr = NEW_ZEROED(int);  // *ptr == 0 guaranteed
FREE(ptr);
```

#### `FREE(ptr)`
Safe free that prevents dangling pointers by setting the pointer to `NULL`.

```c
FREE(ptr);  // Frees memory and sets ptr to NULL
```

---

### Logging, Errors & Assertions

#### `LOG(fmt, ...)`
Print a colored log message to stderr.

```c
LOG("Starting process with value: %d", value);
// Output: [LOG] Starting process with value: 42
```

#### `ERROR(fmt, ...)`
Print an error with file and line number, then exit the program.

```c
if (count < 0) {
    ERROR("Invalid count: %d", count);
}
// Output: [ERROR] main.c:42: Invalid count: -5
// Program exits with EXIT_FAILURE
```

#### `ASSERT(cond, msg)`
Check a condition at runtime; calls `ERROR` with the message if it fails.

```c
ASSERT(ptr != NULL, "pointer must not be NULL");
```

#### `UNIMPLEMENTED()`
Mark a code path as not yet implemented. Calls `ERROR` and exits.

```c
void todo_feature(void) {
    UNIMPLEMENTED();
}
```

#### `UNREACHABLE()`
Mark a code path that should never be reached. Useful in `switch` default branches.

```c
switch (state) {
    case A: ...; break;
    case B: ...; break;
    default: UNREACHABLE();
}
```

---

### Loop Helpers

#### `FOR(i, n)`
Iterate from 0 to n-1 using `size_t`.

```c
FOR(i, 5) {
    printf("%zu\n", i);  // Prints 0, 1, 2, 3, 4
}
```

#### `FOR_RANGE(i, start, end)`
Iterate from start to end-1 (exclusive end).

```c
FOR_RANGE(i, 5, 10) {
    printf("%zu\n", i);  // Prints 5, 6, 7, 8, 9
}
```

---

### String Operations

#### `STREQ(a, b)`
Compare two strings for equality (wrapper around `strcmp`).

```c
if (STREQ(command, "quit")) {
    exit(0);
}
```

#### `STR_EMPTY(s)`
Check if a string is empty (i.e. its first character is `'\0'`).

```c
if (STR_EMPTY(buffer)) {
    LOG("Nothing was entered.");
}
```

#### `STR_STARTS_WITH(s, prefix)`
Check if string `s` begins with `prefix`.

```c
if (STR_STARTS_WITH(path, "/usr")) {
    LOG("System path detected.");
}
```

---

### Compiler Hints *(GCC/Clang only)*

#### `LIKELY(x)` / `UNLIKELY(x)`
Hint to the compiler about branch probability, mapping to `__builtin_expect`. Falls back to a plain identity on other compilers.

```c
if (LIKELY(ptr != NULL)) {
    // fast path
}
if (UNLIKELY(err != 0)) {
    ERROR("Unexpected error: %d", err);
}
```

#### `UNUSED(x)`
Suppress unused-variable warnings. Works on all compilers (expands to `(void)(x)`).

```c
void callback(int UNUSED(unused_param)) { }
```

#### `DEPRECATED` *(GCC/Clang only)*
Mark a function as deprecated so callers get a compile-time warning.

```c
DEPRECATED void old_api(void);
```

#### `NODISCARD` *(GCC/Clang only)*
Warn if the return value of a function is ignored.

```c
NODISCARD int important_result(void);
```

---

### Type Helpers

#### `TYPE_NAME(x)` *(GCC/Clang only)*
Expands to the type of expression `x` using `__typeof__`. Useful for declaring variables with the same type as a given expression.

```c
int value = 5;
TYPE_NAME(value) copy = value;  // copy has the same type as value
```

#### `TYPE_STR(x)`
Returns a string describing the type of `x` for a set of built-in types.

Supported types: `int`, `long`, `float`, `double`, `char`.

```c
int value = 5;
printf("Type: %s\n", TYPE_STR(value));  // Output: Type: int
```

#### `TYPE_FUNC(x)` *(GCC/Clang only)*
Returns the compiler's pretty function signature for debugging.

```c
int value = 5;
printf("%s\n", TYPE_FUNC(value));
// Output: const char* main() [with int = int]
```

#### `PRINT(x)`
Print a variable to stdout with an automatic newline. Uses `_Generic` to dispatch to the correct format specifier.

Supported types: `int`, `long`, `float`, `double`, `char`, `char*`.

```c
int n = 42;
PRINT(n);         // Output: 42

char *s = "hi";
PRINT(s);         // Output: hi
```

---

### Input/Output

#### `read_line(buffer, size)`
Read a line of input from stdin, safely removing the trailing newline.

```c
char buffer[256];
printf("Enter your name: ");
read_line(buffer, sizeof(buffer));
printf("Hello, %s!\n", buffer);
```

---

### Boolean Support

If not using `<stdbool.h>`, the library provides:
- `clibx_bool` - Type for boolean values
- `clibx_true` / `clibx_false` - Boolean constants (1 and 0)
- `CLIBX_PRINT_BOOL(value)` - Print boolean as "true" or "false"

```c
clibx_bool flag = clibx_true;
CLIBX_PRINT_BOOL(flag);  // Output: true
```

---

## clibx_print.h - Optional Standalone Printf

**clibx_print.h** is a completely standalone, optional module that provides a minimal `printf` implementation using Linux x86_64 syscalls directly. It does **not** depend on `libc`'s stdio, making it lightweight for minimal environments or educational purposes.

**Note:** This module is independent and can be used without `clibx.h`.

### Motivation

This is useful when:
- Building minimal/freestanding C programs
- Learning about syscall-level I/O
- Reducing binary dependencies for embedded scenarios
- Teaching low-level C concepts

### API

#### `clibx_printf(fmt, ...)`
Printf-style output to stdout. Supports the following format specifiers:

| Specifier  | Type                                 | Example                                      |
|------------|--------------------------------------|----------------------------------------------|
| `%d`, `%i` | Signed decimal integer               | `clibx_printf("%d\n", -42);` -> `-42`         |
| `%u`       | Unsigned decimal integer             | `clibx_printf("%u\n", 42);` -> `42`           |
| `%o`       | Unsigned octal                       | `clibx_printf("%o\n", 82);` -> `122`          |
| `%x`       | Unsigned hexadecimal (lowercase)     | `clibx_printf("%x\n", 255);` -> `ff`          |
| `%X`       | Unsigned hexadecimal (uppercase)     | `clibx_printf("%X\n", 255);` -> `FF`          |
| `%p`       | Pointer address (hex with 0x prefix) | `clibx_printf("%p\n", ptr);` -> `0xdeadbeef`  |
| `%s`       | String                               | `clibx_printf("%s\n", "hello");` -> `hello`   |
| `%c`       | Character                            | `clibx_printf("%c\n", 'A');` -> `A`           |
| `%%`       | Literal percent                      | `clibx_printf("100%%\n");` -> `100%`          |

```c
#include "clibx_print.h"

clibx_printf("Hello, %s! You have %d points.\n", "Alice", 100);
// Output: Hello, Alice! You have 100 points.

clibx_printf("Hex: %x, Octal: %o, Unsigned: %u\n", 255, 82, 42);
// Output: Hex: ff, Octal: 122, Unsigned: 42

int arr[] = {1, 2, 3};
clibx_printf("Array at: %p\n", (void*)arr);
// Output: Array at: 0x7ffc8b234560
```

#### `clibx_fprintf(fd, fmt, ...)`
Printf-style output to an arbitrary file descriptor. Accepts the same format specifiers as `clibx_printf`.

```c
clibx_fprintf(2, "Error: %s (code: %d)\n", "Something went wrong", 404);  // fd 2 = stderr
clibx_fprintf(1, "Result: 0x%X\n", 0x1234);                               // fd 1 = stdout
```

### Limitations

- Limited format specifier support (see table above)
- No floating-point formatting (`%f`, `%e`, etc.)
- No width/precision modifiers (`.`, `-`, `0` padding, etc.)
- x86-64 Linux only (architecture-specific syscall assembly)
- Not a full libc replacement

### Missing Specifiers

| Specifier  | Type                       | Reason                                    |
|------------|----------------------------|-------------------------------------------|
| `%f`, `%F` | Decimal floating point     | Complex; would require significant code   |
| `%e`, `%E` | Scientific notation        | Complex; requires floating-point handling |
| `%g`, `%G` | Shortest of %e or %f       | Complex; requires floating-point handling |
| `%a`, `%A` | Hexadecimal floating point | Complex; requires floating-point handling |
| `%n`       | Characters written so far  | Not supported; dangerous and rarely used  |

### Implementation Details

- Uses direct Linux `write` syscall via inline assembly
- No buffering: each call directly writes to the file descriptor
- Minimal footprint and zero stdio dependencies

---

## Files

- `clibx.h` - Main header-only utility library
- `clibx_print.h` - Optional lightweight printf implementation (standalone, no dependencies on clibx.h)
- `main.demo.c` - Example program demonstrating `clibx.h` features
- `print.demo.c` - Example of `clibx_print.h`
- `README.md` - This file

## Build & Run the demos

### Build

Use the Makefile:

```bash
make
```

### Run

```bash
# to run the main demo
./bin/main.demo
# to run the demo of clibx_print.h
./bin/print.demo
```

The example program demonstrates:
- Array operations and printing
- Math macros (`MIN`, `MAX`, `CLAMP`, `ABS`, `LERP`, `IS_POWER_OF_2`, `NEXT_POWER_OF_2`)
- Bitwise macros (`BIT`, `SET_BIT`, `CLEAR_BIT`, `TOGGLE_BIT`, `CHECK_BIT`)
- Variable swapping and memory allocation (`NEW`, `NEW_ZEROED`, `FREE`)
- Loop helpers and string operations (`STREQ`, `STR_EMPTY`, `STR_STARTS_WITH`)
- User input with `read_line`
- Logging, assertions, and error handling (`LOG`, `ERROR`, `ASSERT`, `UNIMPLEMENTED`, `UNREACHABLE`)
- Type introspection and generic printing (`TYPE_STR`, `PRINT`)
- Compiler hints (`LIKELY`, `UNLIKELY`, `UNUSED`, `DEPRECATED`, `NODISCARD`)

## Notes

- Both `clibx.h` and `clibx_print.h` are header-only with no separate compilation needed
- `clibx_print.h` is completely optional and can be used independently
- GCC/Clang-specific features are guarded with `#ifdef __GNUC__`; portable fallbacks are provided
- This project is intended as a toolkit for small CLI utilities and as a teaching example for macro-based helpers in C
- Fully portable except for `clibx_print.h`, which requires x86_64 Linux
