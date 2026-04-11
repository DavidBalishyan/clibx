#ifndef CLIBX_H
#define CLIBX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strcmp

// Get the size of an array
#define ARRAY_SIZE(arr) (sizeof arr / sizeof arr[0])

// Print an array 
static inline void print_int_array(const int *arr, size_t len) {
    printf("[");
    for (size_t i = 0; i < len; i++) {
        printf("%d", arr[i]);
        if (i < len - 1) printf(", ");
    }
    printf("]\n");
}

static inline void print_double_array(const double *arr, size_t len) {
    printf("[");
    for (size_t i = 0; i < len; i++) {
        printf("%f", arr[i]);
        if (i < len - 1) printf(", ");
    }
    printf("]\n");
}

static inline void print_char_array(const char *arr, size_t len) {
    printf("[");
    for (size_t i = 0; i < len; i++) {
        printf("'%c'", arr[i]);
        if (i < len - 1) printf(", ");
    }
    printf("]\n");
}
// Return smaller or larger value
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Restricts a value into a range
#define CLAMP(x, min, max) ( (x) < (min) ? (min) : ((x) > (max) ? (max) : (x)) )

// get the absolute value of x
#define ABS(x) ((x) < 0 ? -(x) : (x))


// Swap two variables.
#define SWAP(a, b) do { \
    __typeof__(a) _tmp = (a); \
    (a) = (b); \
    (b) = _tmp; \
} while(0)


// make allocation of variables and arrays safer
#define NEW(type) ((type*)malloc(sizeof(type)))
#define NEW_ARRAY(type, count) ((type*)malloc(sizeof(type) * (count)))

// safer free, prevents dangling pointers
#define FREE(ptr) do { \
    free(ptr); \
    ptr = NULL; \
} while(0)

// utils for debugging
#define LOG(fmt, ...) \
    fprintf(stderr, "\033[1m\033[1;33m[LOG] \033[0m " fmt "\n", ##__VA_ARGS__)

#define ERROR(fmt, ...) do { \
    fprintf(stderr, "\033[1m\033[1;31m[ERROR] \033[0m %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    exit(EXIT_FAILURE); \
} while(0)

// Loop helpers
#define FOR(i, n) for (size_t i = 0; i < (n); i++)
#define FOR_RANGE(i, start, end) for (size_t i = (start); i < (end); i++)

// Boolean (if not using stdbool)
#ifndef __cplusplus
    #ifndef bool
        #define clibx_bool int
        #define clibx_true 1
        #define clibx_false 0
    #endif
#endif

// checks if two strings are equal.
#define STREQ(a, b) (strcmp((a), (b)) == 0)

// safe input
static inline void read_line(char *buffer, size_t size) {
    if (fgets(buffer, size, stdin)) {
        size_t len = 0;
        while (buffer[len] != '\0') len++;
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

#endif // CLIBX_H
