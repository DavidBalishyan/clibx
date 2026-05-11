#include "clibx.h"
#include <stdio.h>

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

    // Math utils
    int a = 10, b = 20;
    printf("clibx_log2(16): %f\n", clibx_log2(16));
    printf("clibx_pow(10, 2): %f\n", clibx_pow(10, 2));
    printf("clibx_ceil(10.2): %f\n", clibx_ceil(10.5));
	printf("clibx_round(10.6): %f\n", clibx_round(10.6));
	printf("clibx_floor(10.9): %f\n", clibx_floor(10.9));
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

    str path_str = "/usr/local/bin";
    printf("STR_STARTS_WITH(\"%s\", \"/usr\"): %s\n",
           path_str, STR_STARTS_WITH(path_str, "/usr") ? "true" : "false");

    str sentence = "The quick brown fox";
    printf("STR_CONTAINS(\"%s\", \"fox\"): %s\n",
           sentence, STR_CONTAINS(sentence, "fox") ? "true" : "false");

    str raw = "  hello world  ";
    str trimmed = strtrim(raw);
    printf("strtrim(\"%s\"): \"%s\"\n", raw, trimmed);
    FREE(trimmed);

    str csv = "one,two,three";
    clibx_str_vec parts = strsplit(csv, ',');
    printf("strsplit(\"%s\", ','): [", csv);
    FOR(i, parts.length) {
        printf("\"%s\"", parts.data[i]);
        if (i < parts.length - 1) printf(", ");
        FREE(parts.data[i]);
    }
    printf("]\n");
    vec_free(&parts);

    str items[] = {"apple", "banana", "cherry"};
    str joined = strjoin(items, ARRAY_SIZE(items), ", ");
    printf("strjoin: \"%s\"\n", joined);
    FREE(joined);

    str lower = strdup("Hello World");
    str_to_lower(lower);
    printf("str_to_lower: \"%s\"\n", lower);
    str_to_upper(lower);
    printf("str_to_upper: \"%s\"\n\n", lower);
    FREE(lower);

    // DYNAMIC ARRAY (Vec)
    clibx_str_vec vec = vec_init();
    vec_push(&vec, "first");
    vec_push(&vec, "second");
    vec_push(&vec, "third");
    printf("clibx_str_vec: length=%zu, capacity=%zu\n", vec.length, vec.capacity);
    FOR(i, vec.length) printf("  vec[%zu] = \"%s\"\n", i, vec.data[i]);
    vec_free(&vec);
    printf("vec freed: length=%zu, capacity=%zu\n\n", vec.length, vec.capacity);

    // PATH UTILITIES
    str full_path = "/usr/local/bin/main.demo";
    str base = path_basename(full_path);
    printf("path_basename: \"%s\"\n", base);
    FREE(base);

    str dir = path_dirname(full_path);
    printf("path_dirname: \"%s\"\n", dir);
    FREE(dir);

    str ext = path_extension(full_path);
    printf("path_extension: \"%s\"\n", ext);
    FREE(ext);

    str dir_no_slash = "/usr/local";
    str bin = "bin";
    str joined_path = path_join(dir_no_slash, bin);
    printf("path_join(\"%s\", \"%s\"): \"%s\"\n", dir_no_slash, bin, joined_path);
    FREE(joined_path);

    printf("path_exists(\".\"): %s\n", path_exists(".") ? "true" : "false");
    printf("path_exists(\"nonexistent\"): %s\n", path_exists("nonexistent") ? "true" : "false");
    printf("path_is_dir(\".\"): %s\n", path_is_dir(".") ? "true" : "false");
    printf("path_is_file(\"clibx.h\"): %s\n", path_is_file("clibx.h") ? "true" : "false");
    printf("path_file_size(\"clibx.h\"): %ld bytes\n\n", path_file_size("clibx.h"));

    // HASH MAP
    clibx_hashmap map = hashmap_init();
    hashmap_put(&map, "name", "Alice");
    hashmap_put(&map, "age", "30");
    hashmap_put(&map, "city", "New York");
    hashmap_put(&map, "name", "Bob"); // overwrite
    printf("hashmap: count=%zu, capacity=%zu\n", map.count, map.capacity);
    printf("  name: \"%s\"\n", hashmap_get(&map, "name"));
    printf("  age: \"%s\"\n", hashmap_get(&map, "age"));
    printf("  city: \"%s\"\n", hashmap_get(&map, "city"));
    printf("  missing: %s\n", hashmap_get(&map, "missing") ? "found" : "NULL");
    printf("  contains(\"age\"): %s\n", hashmap_contains(&map, "age") ? "true" : "false");
    hashmap_free(&map);
    printf("hashmap freed: count=%zu, capacity=%zu\n\n", map.count, map.capacity);

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
