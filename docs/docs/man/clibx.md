# NAME

clibx - minimal C utility library for common programming patterns

# SYNOPSIS

**#include \<clibx.h\>**

# DESCRIPTION

**clibx** is a lightweight, header-only C utility library providing
common macros and helper functions to simplify everyday C development
tasks. It requires only the C standard library and is designed with zero
external dependencies.

# FEATURES

**Array Operations**

:   \- ARRAY_SIZE, print_int_array, print_double_array, print_char_array

**Math Macros**

:   \- MIN, MAX, CLAMP, ABS, LERP, IS_POWER_OF_2, NEXT_POWER_OF_2

**Bitwise Operations**

:   \- BIT, SET_BIT, CLEAR_BIT, TOGGLE_BIT, CHECK_BIT

**Memory Utilities**

:   \- NEW, NEW_ARRAY, NEW_ZEROED, FREE, SWAP

**String Operations**

:   \- STREQ, STR_EMPTY, STR_STARTS_WITH, STR_CONTAINS - strtrim,
    strsplit, strjoin, str_to_lower, str_to_upper

**Dynamic Vector**

:   \- str_vec with vec_init, vec_push, vec_free

**Path Utilities**

:   \- path_basename, path_dirname, path_extension, path_join -
    path_exists, path_is_dir, path_is_file, path_file_size

**Hash Map**

:   \- String-to-string hash map with DJB2 hashing - hashmap_init,
    hashmap_put, hashmap_get, hashmap_contains, hashmap_free

**Logging & Error Handling**

:   \- LOG, ERROR, ASSERT, UNIMPLEMENTED, UNREACHABLE

**Type Introspection**

:   \- TYPE_STR, TYPE_NAME, TYPE_FUNC, PRINT

**Compiler Hints (GCC/Clang)**

:   \- LIKELY, UNLIKELY, UNUSED, DEPRECATED, NODISCARD, SWAP

**Loop Helpers**

:   \- FOR, FOR_RANGE

# DATA TYPES

**str**

:   String type alias for char\*

**str_vec**

:   Dynamic string vector

        typedef struct {
            str *data;
            size_t length;
            size_t capacity;
        } str_vec;

**clibx_hashmap**

:   String-to-string hash map

        typedef struct {
            clibx_hashmap_entry **buckets;
            size_t capacity;
            size_t count;
        } clibx_hashmap;

# MEMORY MANAGEMENT

All memory functions are convenience wrappers around malloc/calloc/free:

**NEW(type)**

:   Allocate memory for a single object. Returns pointer or exits on
    failure.

**NEW_ARRAY(type, count)**

:   Allocate array of given type and count.

**NEW_ZEROED(type)**

:   Allocate and zero-initialize a single object.

**FREE(ptr)**

:   Free memory and set pointer to NULL (prevents dangling pointers).

# EXAMPLE

    #include <clibx.h>

    int main(void) {
        // Array operations
        int arr[] = {1, 2, 3, 4, 5};
        print_int_array(arr, ARRAY_SIZE(arr));

        // Math operations
        int min = MIN(10, 20);
        int max = MAX(10, 20);

        // Memory allocation
        int *ptr = NEW(int);
        *ptr = 42;
        FREE(ptr);

        // String operations
        str text = "  hello world  ";
        str trimmed = strtrim(text);
        printf("Trimmed: '%s', trimmed);
        FREE(trimmed);

        // Logging
        LOG("Application started");
        if (ptr == NULL)
            ERROR("Pointer is NULL");

        return 0;
    }

# COMPILATION

Compile with all necessary dependencies:

    gcc -lm myprogram.c -o myprogram

# PORTABILITY NOTES

**GCC/Clang Only Features**

:   SWAP, LIKELY, UNLIKELY, DEPRECATED, NODISCARD, TYPE_NAME, TYPE_FUNC
    provide portable no-op fallbacks on other compilers.

**POSIX Features**

:   Path utilities require POSIX functions (access, stat, basename,
    dirname) and work on Unix-like systems (Linux, macOS, BSD).

**Boolean Support**

:   If \<stdbool.h\> is not available, clibx_bool, clibx_true,
    clibx_false are provided. Use clibx_bool for boolean values in
    pre-C99 code.

# SEE ALSO

**clibx_list**(3), **clibx_print**(3)

# AUTHOR

DavidBalishyan \<davidbalishyan12@gmail.com\>

# BUGS

Report bugs to the project repository.

# LICENSE

See LICENSE file in the project root.
