#include "clibx.h"

int main() {
    // ARRAY_SIZE
    int arr[] = {1, 2, 3, 4, 5};
    size_t len = ARRAY_SIZE(arr);
    print_int_array(arr, ARRAY_SIZE(arr));
    printf("Array size: %zu\n\n", len);

    // MIN / MAX / CLAMP / ABS
    int a = 10, b = 20;

    printf("MIN: %d\n", MIN(a, b));
    printf("MAX: %d\n", MAX(a, b));
    printf("CLAMP(25, 0, 15): %d\n", CLAMP(25, 0, 15));
    printf("ABS(-42): %d\n\n", ABS(-42));

    // SWAP
    printf("Before swap: a=%d, b=%d\n", a, b);
    SWAP(a, b);
    printf("After swap: a=%d, b=%d\n\n", a, b);

    // MEMORY (NEW / NEW_ARRAY / FREE)
    int *x = NEW(int);
    if (!x) {
        ERROR("Failed to allocate memory for x");
    }
    *x = 99;
    printf("Allocated int: %d\n", *x);

    int *numbers = NEW_ARRAY(int, 5);
    if (!numbers) {
        ERROR("Failed to allocate array");
    }

    FOR(i, 5) {
        numbers[i] = i * 2;
    }

    printf("Dynamic array: ");
    FOR(i, 5) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    FREE(x);
    FREE(numbers);
    printf("Memory freed.\n\n");

    // LOG
    LOG("This is a log message with value=%d", 123);

    // LOOP HELPERS
    printf("\nFOR loop:\n");
    FOR(i, 3) {
        printf("i = %zu\n", i);
    }

    printf("\nFOR_RANGE loop:\n");
    FOR_RANGE(i, 5, 8) {
        printf("i = %zu\n", i);
    }

    // BOOLEAN
    clibx_bool flag = clibx_true;
    printf("\nBoolean works: ");
		CLIBX_PRINT_BOOL(flag);

    // TYPE HELPERS
    int value = 5;
    TYPE_NAME(value) same_type_value = value;
    printf("Type of value: %s\n", TYPE_STR(value));
    printf("Same-type value: %d\n", same_type_value);
    printf("Type function info: %s\n", TYPE_FUNC(value));

    // STRING (STREQ)
    if (STREQ("hello", "hello")) {
        printf("Strings are equal\n");
    }

    // SAFE INPUT (read_line)
    char buffer[100];
    printf("\nEnter something: ");
    read_line(buffer, sizeof(buffer));
    printf("You entered: %s\n", buffer);

    return 0;
}
