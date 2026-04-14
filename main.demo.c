#include "clibx.h"

int main() {
    // ARRAY_SIZE & printing
    int arr[] = {1, 2, 3, 4, 5};
    size_t len = ARRAY_SIZE(arr);
    print_int_array(arr, len);
    printf("Array size: %zu\n\n", len);

    // MIN / MAX / CLAMP / ABS 
    int a = 10, b = 20;
    printf("MIN: %d\n",               MIN(a, b));
    printf("MAX: %d\n",               MAX(a, b));
    printf("CLAMP(25, 0, 15): %d\n",  CLAMP(25, 0, 15));
    printf("ABS(-42): %d\n\n",        ABS(-42));

    // LERP 
    double lerp_result = LERP(0.0, 100.0, 0.25);
    printf("LERP(0, 100, 0.25): %.2f\n\n", lerp_result);

    // IS_POWER_OF_2 / NEXT_POWER_OF_2 
    printf("IS_POWER_OF_2(8): %s\n",  IS_POWER_OF_2(8)  ? "true" : "false");
    printf("IS_POWER_OF_2(6): %s\n",  IS_POWER_OF_2(6)  ? "true" : "false");
    printf("NEXT_POWER_OF_2(5): %d\n",  NEXT_POWER_OF_2(5));
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

    // LOOP HELPERS 
    printf("FOR loop:\n");
    FOR(i, 3) printf("  i = %zu\n", i);

    printf("FOR_RANGE loop:\n");
    FOR_RANGE(i, 5, 8) printf("  i = %zu\n", i);
    printf("\n");

    // LIKELY / UNLIKELY
    int err = 0;
    if (LIKELY(err == 0))   printf("LIKELY:   no error (expected path)\n");
    if (UNLIKELY(err != 0)) printf("UNLIKELY: error path (should not print)\n");
    printf("\n");

    // UNUSED 
    int unused_var = 42;
    UNUSED(unused_var);
    printf("UNUSED: suppressed warning for unused_var\n\n");

    // BOOLEAN 
    clibx_bool flag = clibx_true;
    printf("Boolean: ");
    CLIBX_PRINT_BOOL(flag);
    printf("\n");

    // STRING UTILITIES
    if (STREQ("hello", "hello"))
        printf("STREQ: strings are equal\n");

    char empty[] = "";
    printf("STR_EMPTY(\"\"): %s\n", STR_EMPTY(empty) ? "true" : "false");

    char path[] = "/usr/local/bin";
    printf("STR_STARTS_WITH(\"%s\", \"/usr\"): %s\n\n",
           path, STR_STARTS_WITH(path, "/usr") ? "true" : "false");

    // TYPE HELPERS
    int value = 5;
    TYPE_NAME(value) same_type_value = value;
    printf("TYPE_STR:  %s\n",   TYPE_STR(value));
    printf("TYPE_NAME: %d (same type as value)\n", same_type_value);
    printf("TYPE_FUNC: %s\n\n", TYPE_FUNC(value));

    // PRINT (generic) 
    printf("PRINT macro (generic dispatch):\n");
    int    pi = 42;
    long   pl = 123456789L;
    double pd = 3.14;
    char   pc = 'Z';
    char  *ps = "hello";
    printf("  int:    "); PRINT(pi);
    printf("  long:   "); PRINT(pl);
    printf("  double: "); PRINT(pd);
    printf("  char:   "); PRINT(pc);
    printf("  char*:  "); PRINT(ps);
    printf("\n");

    // Safe input
    char buffer[100];
    printf("Enter something: ");
    read_line(buffer, sizeof(buffer));
    printf("You entered: %s\n", buffer);

    return 0;
}