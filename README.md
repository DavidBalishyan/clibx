>[!NOTE]
>This README is also available as a documentation site [here](https://davidbalishyan.github.io/clibx) 

# clibx

A small, header-only C utility library with common macros and helper functions designed to simplify everyday C development tasks.

## Table of Contents

- [Overview](#overview)
- [Installation](#installation)
- [clibx.h - Main Library](#clibxh---main-library)
  - [String type](#str)
  - [Array Operations](#array-operations)
  - [Math Operations](#math-operations)
  - [Bitwise Operations](#bitwise-operations)
  - [Variable Operations](#variable-operations)
  - [Memory Management](#memory-management)
  - [Loop Helpers](#loop-helpers)
  - [Compiler Hints](#compiler-hints-gccclang-only)
  - [Type Helpers](#type-helpers)
  - [Logging, Errors & Assertions](#logging-errors--assertions)
  - [Boolean Support](#boolean-support)
  - [String Operations](#string-operations)
  - [Dynamic Array (Vec)](#dynamic-array-vec)
  - [Path Utilities](#path-utilities)
  - [Hash Map](#hash-map)
  - [Input/Output](#inputoutput)
- [clibx_list.h - Linked List](#clibx_listh---linked-list)
- [clibx_print.h - Optional Standalone Printf](#clibx_printh---optional-standalone-printf)
- [Files](#files)
- [Build & Run the demos](#build--run-the-demos)

## Overview

**clibx** provides lightweight, macro-based utilities for common C programming patterns, reducing boilerplate and improving code readability. Everything is header-only with zero dependencies beyond the C standard library.

Features include:
- Array helpers and printing utilities
- Math macros (`MIN`, `MAX`, `CLAMP`, `ABS`, `LERP`, power-of-2 checks)
- Memory allocation helpers (`NEW`, `NEW_ARRAY`, `NEW_ZEROED`, `FREE`)
- Bitwise operations (`BIT`, `SET_BIT`, `CLEAR_BIT`, `TOGGLE_BIT`, `CHECK_BIT`)
- Dynamic string vector (`str_vec`)
- String operations (trim, split, join, case conversion)
- Path utilities (basename, dirname, extension, join, exists, size)
- String-to-string hash map
- Loop helpers (`FOR`, `FOR_RANGE`)
- Logging, assertions, and error handling
- Type introspection (`TYPE_STR`, `PRINT`, `TYPE_NAME`)
- Compiler hints (`LIKELY`, `UNLIKELY`, `UNUSED`, `DEPRECATED`, `NODISCARD`)
- **Singly-linked list** with generic data storage
- **Lightweight printf** using direct syscalls

> **Portability note:** Most of `clibx.h` is standard C11. Features inside the `#ifdef __GNUC__` block (`SWAP`, `LIKELY`, `UNLIKELY`, `DEPRECATED`, `NODISCARD`, `TYPE_NAME`, `TYPE_FUNC`) require GCC or Clang. Safe no-op fallbacks are provided for other compilers.

## Installation

See [INSTALL.md](INSTALL.md) for comprehensive installation instructions including system-wide installation, custom prefixes, and single-header downloads.

## clibx.h - Main Library

#### `str`
An alias over `char*` to improve DX and code readability

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

#### `STR_CONTAINS(haystack, needle)`
Check if `haystack` contains `needle` (wrapper around `strstr`).

```c
if (STR_CONTAINS(filename, ".txt")) {
    LOG("Text file detected.");
}
```

#### `strtrim(s)`
Returns a newly allocated string with leading and trailing whitespace removed. Caller must free the result.

```c
str original = "  hello world  ";
str trimmed = strtrim(original);
printf("%s\n", trimmed);  // Output: "hello world"
FREE(trimmed);
```

#### `strsplit(input, delim)`
Splits a string by delimiter into a `str_vec`. Caller must free the vector and individual strings.

```c
str_vec parts = strsplit("one,two,three", ',');
FOR(i, parts.length) {
    printf("%s\n", parts.data[i]);
    FREE(parts.data[i]);
}
vec_free(&parts);
```

#### `strjoin(arr, len, sep)`
Joins an array of strings with a separator. Returns a newly allocated string. Caller must free.

```c
str items[] = {"apple", "banana", "cherry"};
str result = strjoin(items, 3, ", ");
printf("%s\n", result);  // Output: "apple, banana, cherry"
FREE(result);
```

#### `str_to_lower(s)` / `str_to_upper(s)`
Converts string to lowercase or uppercase in place. Returns the same pointer.

```c
str text = strdup("Hello World");
str_to_lower(text);  // text is now "hello world"
str_to_upper(text);  // text is now "HELLO WORLD"
FREE(text);
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

### Dynamic Array (Vec)

#### `str_vec`
A dynamic array type for storing strings (`str*`).

```c
typedef struct {
    str *data;
    size_t length;
    size_t capacity;
} str_vec;
```

#### `vec_init()`
Initialize an empty string vector.

```c
str_vec vec = vec_init();
```

#### `vec_push(vec, value)`
Append a string to the vector. Automatically doubles capacity when full (starts at 8).

```c
str_vec vec = vec_init();
vec_push(&vec, "hello");
vec_push(&vec, "world");
```

#### `vec_free(vec)`
Free the vector's internal data buffer. Does NOT free individual strings.

```c
vec_free(&vec);
```

---

### Path Utilities

#### `path_basename(path)`
Returns the filename component of a path. Caller must free.

```c
str base = path_basename("/usr/local/bin/foo");
printf("%s\n", base);  // Output: "foo"
FREE(base);
```

#### `path_dirname(path)`
Returns the directory component of a path. Caller must free.

```c
str dir = path_dirname("/usr/local/bin/foo");
printf("%s\n", dir);  // Output: "/usr/local/bin"
FREE(dir);
```

#### `path_extension(path)`
Returns the file extension without the dot, or empty string. Caller must free.

```c
str ext = path_extension("file.txt");
printf("%s\n", ext);  // Output: "txt"
FREE(ext);
```

#### `path_join(a, b)`
Joins two path components with `/`. Returns a newly allocated string. Caller must free.

```c
str full = path_join("/usr/local", "bin");
printf("%s\n", full);  // Output: "/usr/local/bin"
FREE(full);
```

#### `path_exists(path)`
Checks if a path exists on disk.

```c
if (path_exists("/etc/passwd")) {
    LOG("File exists");
}
```

#### `path_is_dir(path)` / `path_is_file(path)`
Checks if a path is a directory or regular file.

```c
if (path_is_dir("/usr")) {
    LOG("It's a directory");
}
if (path_is_file("/etc/passwd")) {
    LOG("It's a file");
}
```

#### `path_file_size(path)`
Returns file size in bytes, or -1 on error.

```c
long size = path_file_size("data.txt");
printf("Size: %ld bytes\n", size);
```

---

### Hash Map

#### `clibx_hashmap`
A string-to-string hash map using DJB2 hashing with chaining.

```c
typedef struct {
    clibx_hashmap_entry **buckets;
    size_t capacity;
    size_t count;
} clibx_hashmap;
```

#### `hashmap_init()`
Create a new empty hashmap (default capacity: 64).

```c
clibx_hashmap map = hashmap_init();
```

#### `hashmap_put(map, key, value)`
Insert or update a key-value pair.

```c
hashmap_put(&map, "name", "Alice");
hashmap_put(&map, "age", "30");
```

#### `hashmap_get(map, key)`
Get value by key. Returns NULL if not found.

```c
str name = hashmap_get(&map, "name");
printf("%s\n", name);  // Output: "Alice"
```

#### `hashmap_contains(map, key)`
Check if key exists in hashmap.

```c
if (hashmap_contains(&map, "name")) {
    LOG("Name is set");
}
```

#### `hashmap_free(map)`
Free all memory used by the hashmap.

```c
hashmap_free(&map);
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

## clibx_list.h - Linked List

**`clibx_list.h`** provides a generic, type-agnostic singly-linked list implementation. It uses void pointers to store arbitrary data, supporting any data type (primitives, strings, structs, etc.).

>[!NOTE]
>This module requires `clibx.h` and is header-only

### Overview

The linked list implementation includes:
- **Fast operations:** O(1) `push_front`, `push_back`, `pop_front`; O(n) `get`, `remove_at`, `contains`
- **Generic design:** Works with any data type via void pointers
- **Memory efficiency:** Optimized tail pointer for O(1) `push_back`
- **Easy iteration:** Convenient macros for traversing the list
- **Type-safe callbacks:** Support for custom comparison functions

### Core Data Structures

#### `clibx_node`
Individual linked list node.

```c
typedef struct clibx_node {
    void *data;           // Pointer to user data
    struct clibx_node *next;  // Next node
} clibx_node;
```

#### `clibx_list`
The linked list container.

```c
typedef struct {
    clibx_node *head;     // First node
    clibx_node *tail;     // Last node (for O(1) append)
    size_t count;         // Number of elements
} clibx_list;
```

### API Reference

#### `list_init()`
Initialize an empty linked list.

```c
clibx_list list = list_init();
```

#### `list_push_back(list, data)`
Append data to the end of the list. O(1) operation.

```c
int *val = NEW(int);
*val = 42;
list_push_back(&list, val);
```

#### `list_push_front(list, data)`
Prepend data to the beginning of the list. O(1) operation.

```c
int *val = NEW(int);
*val = 10;
list_push_front(&list, val);
```

#### `list_get(list, index)`
Get data at a specific 0-based index. Returns NULL if out of bounds. O(n) operation.

```c
void *data = list_get(&list, 2);
if (data) printf("%d\n", *(int*)data);
```

#### `list_front(list)` / `list_back(list)`
Get data at the front or back of the list. O(1) operations.

```c
int *first = (int*)list_front(&list);
int *last = (int*)list_back(&list);
```

#### `list_contains(list, value, cmp)`
Check if a value exists using a comparison function. O(n) operation.

```c
int target = 42;
int found = list_contains(&list, &target, (int (*)(void*, void*))int_cmp);

int int_cmp(int *a, int *b) {
    return *a == *b;
}
```

#### `list_pop_front(list)`
Remove and return the first element. Caller is responsible for freeing the data. O(1) operation.

```c
void *data = list_pop_front(&list);
if (data) {
    printf("%d\n", *(int*)data);
    free(data);
}
```

#### `list_remove_at(list, index)`
Remove and return element at a specific index. Caller is responsible for freeing. O(n) operation.

```c
void *data = list_remove_at(&list, 1);
if (data) free(data);
```

#### `list_remove_all(list, free_data)`
Remove all nodes from the list. If `free_data` is non-zero, frees each node's data as well. O(n) operation.

```c
list_remove_all(&list, 1);  // Remove all and free data
list_remove_all(&list, 0);  // Remove all, but don't free data
```

#### `list_is_empty(list)` / `list_size(list)`
Check if list is empty or get the element count. O(1) operations.

```c
if (list_is_empty(&list)) {
    printf("List is empty\n");
} else {
    printf("List has %zu elements\n", list_size(&list));
}
```

#### `list_free(list, free_data)`
Free all memory used by the list. If `free_data` is non-zero, also frees each node's data. O(n) operation.

```c
list_free(&list, 1);  // Free entire list and all data
```

#### `list_print_int(list)` / `list_print_str(list)`
Print all integers or strings in the list in `[a, b, c]` format.

```c
list_print_int(&int_list);      // Output: [10, 20, 30]
list_print_str(&string_list);   // Output: ["apple", "banana"]
```

### Iteration Macros

#### `LIST_FOR_EACH(node, list)`
Iterate over all nodes in the list, accessing the node structure directly.

```c
clibx_node *node;
LIST_FOR_EACH(node, &list) {
    printf("%d\n", *(int*)node->data);
}
```

### Complete Example

```c
#include "clibx_list.h"

int main(void) {
    clibx_list list = list_init();
    
    // Add integers
    int *a = NEW(int); *a = 10;
    int *b = NEW(int); *b = 20;
    int *c = NEW(int); *c = 30;
    
    list_push_back(&list, a);
    list_push_back(&list, b);
    list_push_back(&list, c);
    
    printf("List: ");
    list_print_int(&list);  // [10, 20, 30]
    
    // Access elements
    int *first = (int*)list_front(&list);
    printf("First: %d\n", *first);  // 10
    
    // Remove front
    void *removed = list_pop_front(&list);
    printf("Removed: %d\n", *(int*)removed);
    free(removed);
    
    printf("List: ");
    list_print_int(&list);  // [20, 30]
    
    // Iterate and print
    printf("Iterate: ");
    void *data;
    LIST_FOR_EACH_DATA(data, &list) {
        printf("%d ", *(int*)data);
    }
    printf("\n");
    
    // Clean up
    list_free(&list, 1);
    
    return 0;
}
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

**`clibx_print.h`** is a completely standalone, optional module that provides a minimal `printf` implementation using Linux x86_64 syscalls directly. It does **not** depend on `libc`'s stdio, making it lightweight for minimal environments or educational purposes.

>[!NOTE]
>This module is independent and can be used without `clibx.h`

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
- `clibx_list.h` - Singly linked list implementation (header-only)
- `clibx_print.h` - Optional lightweight printf implementation (standalone, no dependencies on clibx.h)
- `main.demo.c` - Example program demonstrating `clibx.h` features
- `list.demo.c` - Example of `clibx_list.h` features
- `print.demo.c` - Example of `clibx_print.h`
- `man/man3/clibx.3` - Comprehensive manpage for `clibx.h`
- `man/man3/clibx_list.3` - Comprehensive manpage for `clibx_list.h`
- `man/man3/clibx_print.3` - Comprehensive manpage for `clibx_print.h`
- `Makefile` - Build and installation configuration
- `INSTALL.md` - Installation and setup guide
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

# to run the linked list demo
./bin/list.demo

# to run the demo of clibx_print.h
./bin/print.demo
```

The example programs demonstrate:
- **main.demo.c**: Array operations and printing, math macros, bitwise operations, memory allocation, loop helpers, string operations, dynamic vector, path utilities, hash maps, type introspection, compiler hints, logging, and assertions
- **list.demo.c**: Linked list operations including push/pop, element access, searching, iteration, and custom data types
- **print.demo.c**: Direct syscall-based printf functionality

## Documentation

Comprehensive manpages are provided for offline reference:

### Reading Manpages

After installation (see [Installation](#installation) and [INSTALL.md](INSTALL.md)):

```bash
man clibx          # Main library (all core utilities)
man clibx_list     # Linked list API and examples
man clibx_print    # Lightweight printf implementation
```

### Manpage Contents

#### clibx(3)
Complete reference for `clibx.h` including:
- All data types and structures
- Memory management functions and macros
- String operations with examples
- Path utilities
- Hash map API
- Logging and error handling
- Time complexity analysis
- Usage examples

#### clibx_list(3)
Complete reference for `clibx_list.h` including:
- Linked list data structures and design
- All insertion, access, and removal operations
- Search and iteration
- Custom data type examples (structs)
- Comparator functions for searching
- Time complexity table
- Memory management guidelines

#### clibx_print(3)
Complete reference for `clibx_print.h` including:
- Direct syscall-based printf implementation
- Supported format specifiers with examples
- Platform requirements
- Limitations and feature matrix vs. standard printf
- Educational and use-case information
- Minimal program examples

### Online Documentation

- README.md (this file) - Quick reference and examples
- INSTALL.md - Installation and setup guide
- Source code - Well-commented headers for detailed implementation notes

---

## Notes

- `clibx.h` is header-only with no separate compilation needed
- `clibx_list.h` is completely optional and can be used independently
- `clibx_print.h` is completely optional and can be used independently
- GCC/Clang-specific features are guarded with `#ifdef __GNUC__`; portable fallbacks are provided
- Path utilities use POSIX functions (`access`, `stat`, `basename`, `dirname`) and work on Unix-like systems
- `clibx_print.h` requires x86_64 Linux (uses inline assembly for syscalls)
- This project is intended as a toolkit for small CLI utilities and as a teaching example for macro-based helpers in C
