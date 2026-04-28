#include "clibx.h"

// Example for NODISCARD
NODISCARD int must_use_result() {
    return 123;
}

// Example for DEPRECATED
DEPRECATED void old_function() {
    printf("This function is deprecated\n");
}

int main() {
    // ARRAY_SIZE & printing
    int arr[] = {1, 2, 3, 4, 5};
    double darr[] = {1.1, 2.2, 3.3};
    char carr[] = {'a', 'b', 'c'};

    size_t len = ARRAY_SIZE(arr);
    print_int_array(arr, len);
    print_double_array(darr, ARRAY_SIZE(darr));
    print_char_array(carr, ARRAY_SIZE(carr));
    printf("Array size: %zu\n\n", len);

    // MIN / MAX / CLAMP / ABS
    int a = 10, b = 20;
    printf("MIN: %d\n", MIN(a, b));
    printf("MAX: %d\n", MAX(a, b));
    printf("CLAMP(25, 0, 15): %d\n", CLAMP(25, 0, 15));
    printf("CLAMP(-5, 0, 10): %d\n", CLAMP(-5, 0, 10));
    printf("ABS(-42): %d\n\n", ABS(-42));

    // LERP
    double lerp_result = LERP(0.0, 100.0, 0.25);
    printf("LERP(0, 100, 0.25): %.2f\n\n", lerp_result);

    // IS_POWER_OF_2 / NEXT_POWER_OF_2
    printf("IS_POWER_OF_2(8): %s\n", IS_POWER_OF_2(8) ? "true" : "false");
    printf("IS_POWER_OF_2(6): %s\n", IS_POWER_OF_2(6) ? "true" : "false");
    printf("NEXT_POWER_OF_2(5): %d\n", NEXT_POWER_OF_2(5));
    printf("NEXT_POWER_OF_2(8): %d\n\n", NEXT_POWER_OF_2(8));

    // SWAP
    printf("Before swap: a=%d, b=%d\n", a, b);
    SWAP(a, b);
    printf("After swap:  a=%d, b=%d\n\n", a, b);

    // NEW / NEW_ARRAY / NEW_ZEROED / FREE
    int *x = NEW(int);
    ASSERT(x != NULL, "Failed to allocate memory for x");
    *x = 99;
    printf("NEW int: %d\n", *x);

    int *zeroed = NEW_ZEROED(int);
    ASSERT(zeroed != NULL, "Failed to allocate zeroed int");
    printf("NEW_ZEROED int: %d\n", *zeroed);

    int *numbers = NEW_ARRAY(int, 5);
    ASSERT(numbers != NULL, "Failed to allocate array");
    FOR(i, 5) numbers[i] = (int)i * 2;
    printf("Dynamic array: ");
    FOR(i, 5) printf("%d ", numbers[i]);
    printf("\n");

    FREE(x);
    FREE(zeroed);
    FREE(numbers);
    printf("Memory freed. (x=%p, zeroed=%p, numbers=%p)\n\n",
           (void*)x, (void*)zeroed, (void*)numbers);

    // LOG
    LOG("Log message with value=%d", 123);
    printf("\n");

    // ASSERT
    int positive = 5;
    ASSERT(positive > 0, "positive must be > 0");
    printf("ASSERT passed for positive=%d\n\n", positive);

    // BITWISE OPERATIONS
    int flags = 0;
    SET_BIT(flags, 0); // flags = 1
    SET_BIT(flags, 2); // flags = 5
    printf("BITWISE: SET_BIT 0 and 2 -> flags = %d\n", flags);
    printf("BITWISE: CHECK_BIT 2 -> %s\n", CHECK_BIT(flags, 2) ? "true" : "false");
    printf("BITWISE: CHECK_BIT 1 -> %s\n", CHECK_BIT(flags, 1) ? "true" : "false");
    TOGGLE_BIT(flags, 1); // flags = 7
    printf("BITWISE: TOGGLE_BIT 1 -> flags = %d\n", flags);
    CLEAR_BIT(flags, 0); // flags = 6
    printf("BITWISE: CLEAR_BIT 0 -> flags = %d\n\n", flags);

    // LOOP HELPERS
    printf("FOR loop:\n");
    FOR(i, 3) printf("  i = %zu\n", i);

    printf("FOR_RANGE loop:\n");
    FOR_RANGE(i, 5, 8) printf("  i = %zu\n", i);
    printf("\n");

    // LIKELY / UNLIKELY
    int err = 0;
    if (LIKELY(err == 0)) {
        printf("LIKELY: fast path executed\n");
    } else if (UNLIKELY(err != 0)) {
        printf("UNLIKELY: error path\n");
    }
    printf("\n");

    // UNUSED
    int unused_var = 42;
    UNUSED(unused_var);
    printf("UNUSED: suppressed warning\n\n");

    // BOOLEAN
    clibx_bool flag = clibx_true;
    printf("Boolean: ");
    CLIBX_PRINT_BOOL(flag);
    printf("\n");

    // STRING UTILITIES
    str s1 = "hello";
    str s2 = "hello";
    str s3 = "";

    if (STREQ(s1, s2))
        printf("STREQ: \"%s\" == \"%s\"\n", s1, s2);

    printf("STR_EMPTY: \"%s\" -> %s\n", s3, STR_EMPTY(s3) ? "true" : "false");

    str path = "/usr/local/bin";
    printf("STR_STARTS_WITH(\"%s\", \"/usr\"): %s\n\n",
           path, STR_STARTS_WITH(path, "/usr") ? "true" : "false");

    // TYPE HELPERS
    int value = 5;
    TYPE_NAME(value) same_type_value = value;
    printf("TYPE_STR:  %s\n", TYPE_STR(value));
    printf("TYPE_NAME: %d\n", same_type_value);
    printf("TYPE_FUNC: %s\n\n", TYPE_FUNC(value));

    // PRINT (generic)
    printf("PRINT macro:\n");
    int    pi = 42;
    long   pl = 123456789L;
    double pd = 3.14;
    char   pc = 'Z';
    str    ps = "hello from str";
    printf("  int:    "); PRINT(pi);
    printf("  long:   "); PRINT(pl);
    printf("  double: "); PRINT(pd);
    printf("  char:   "); PRINT(pc);
    printf("  str:    "); PRINT(ps);
    printf("\n");

    // NODISCARD
    int important = must_use_result();
    printf("NODISCARD result: %d\n\n", important);

    // DEPRECATED
    old_function();
    printf("\n");

    // Safe input using `str`
    char buffer[100];
    printf("Enter something: ");
    read_line(buffer, sizeof(buffer));

    str input = buffer;  // alias usage
    printf("You entered: %s\n", input);

    return 0;
}
