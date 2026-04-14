#ifndef CLIBX_PRINT_H
#define CLIBX_PRINT_H

// Minimal types
typedef __builtin_va_list va_list;
#define va_start __builtin_va_start
#define va_arg   __builtin_va_arg
#define va_end   __builtin_va_end

// Linux syscall: write
static long _sys_write(int fd, const void *buf, unsigned long count) {
    long ret;
    __asm__ volatile (
        "mov $1, %%rax\n"
        "syscall"
        : "=a"(ret)
        : "D"(fd), "S"(buf), "d"(count)
        : "rcx", "r11", "memory"
    );
    return ret;
}

// Output helpers
static void _fd_putchar(int fd, char c) {
    _sys_write(fd, &c, 1);
}

static void _fd_putstr(int fd, const char *s) {
    while (*s) _fd_putchar(fd, *s++);
}

static void _fd_putint(int fd, int n) {
    char buf[12];
    int i = 0;
    long num = n;

    if (num == 0) {
        _fd_putchar(fd, '0');
        return;
    }

    if (num < 0) {
        _fd_putchar(fd, '-');
        num = -num;
    }

    while (num > 0) {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }

    while (i--) {
        _fd_putchar(fd, buf[i]);
    }
}

static void _fd_putint_u(int fd, unsigned int n) {
    char buf[20];
    int i = 0;
    unsigned long num = n;

    if (num == 0) {
        _fd_putchar(fd, '0');
        return;
    }

    while (num > 0) {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }

    while (i--) {
        _fd_putchar(fd, buf[i]);
    }
}

static void _fd_putoct(int fd, unsigned int n) {
    char buf[12];
    int i = 0;
    unsigned long num = n;

    if (num == 0) {
        _fd_putchar(fd, '0');
        return;
    }

    while (num > 0) {
        buf[i++] = (num % 8) + '0';
        num /= 8;
    }

    while (i--) {
        _fd_putchar(fd, buf[i]);
    }
}

static void _fd_puthex(int fd, unsigned int n, int uppercase) {
    char buf[10];
    int i = 0;
    unsigned long num = n;
    const char *hex_digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";

    if (num == 0) {
        _fd_putchar(fd, '0');
        return;
    }

    while (num > 0) {
        buf[i++] = hex_digits[num % 16];
        num /= 16;
    }

    while (i--) {
        _fd_putchar(fd, buf[i]);
    }
}

static void _fd_putptr(int fd, void *ptr) {
    _fd_putstr(fd, "0x");
    unsigned long addr = (unsigned long)ptr;
    const char *hex_digits = "0123456789abcdef";
    char buf[20];
    int i = 0;

    if (addr == 0) {
        _fd_putchar(fd, '0');
        return;
    }

    while (addr > 0) {
        buf[i++] = hex_digits[addr % 16];
        addr /= 16;
    }

    while (i--) {
        _fd_putchar(fd, buf[i]);
    }
}

// Core formatter
static void _clibx_vfprintf(int fd, const char *fmt, va_list args) {
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 's': {
                    char *s = va_arg(args, char*);
                    _fd_putstr(fd, s ? s : "(null)");
                    break;
                }
                case 'd':
                case 'i': {
                    int d = va_arg(args, int);
                    _fd_putint(fd, d);
                    break;
                }
                case 'u': {
                    unsigned int u = va_arg(args, unsigned int);
                    _fd_putint_u(fd, u);
                    break;
                }
                case 'o': {
                    unsigned int o = va_arg(args, unsigned int);
                    _fd_putoct(fd, o);
                    break;
                }
                case 'x': {
                    unsigned int x = va_arg(args, unsigned int);
                    _fd_puthex(fd, x, 0);
                    break;
                }
                case 'X': {
                    unsigned int X = va_arg(args, unsigned int);
                    _fd_puthex(fd, X, 1);
                    break;
                }
                case 'p': {
                    void *p = va_arg(args, void*);
                    _fd_putptr(fd, p);
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    _fd_putchar(fd, c);
                    break;
                }
                case '%': {
                    _fd_putchar(fd, '%');
                    break;
                }
                default: {
                    _fd_putchar(fd, '%');
                    _fd_putchar(fd, *fmt);
                }
            }
        } else {
            _fd_putchar(fd, *fmt);
        }
        fmt++;
    }
}

// Public API
// stdout = fd 1
static void clibx_printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    _clibx_vfprintf(1, fmt, args);
    va_end(args);
}

// generic fprintf (fd-based)
static void clibx_fprintf(int fd, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    _clibx_vfprintf(fd, fmt, args);
    va_end(args);
}

#endif /* CLIBX_PRINT_H */
