#include "clibx_print.h"

int main() {
    clibx_printf("Hello, World!\n");
    clibx_printf("Integer: %d\n", 42);
    clibx_printf("Unsigned: %u\n", 42U);
    clibx_printf("Octal: %o\n", 42U);
    clibx_printf("Hex (lower): %x\n", 42U);
    clibx_printf("Hex (upper): %X\n", 42U);
    clibx_printf("Pointer: %p\n", (void*)0x1234);
    clibx_printf("Character: %c\n", 'A');
    clibx_printf("String: %s\n", "Hello, C17!");
    return 0;
}