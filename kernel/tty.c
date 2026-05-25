#include <kernel/tty.h>
#include <stdarg.h>

static uint16_t* const VGA_BUFFER = (uint16_t*)0xB8000;
static const int VGA_WIDTH = 80;
static const int VGA_HEIGHT = 25;

static int tty_row;
static int tty_col;
static uint8_t tty_color;

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t)uc | (uint16_t)color << 8;
}

void tty_init(void) {
    tty_row = 0;
    tty_col = 0;
    tty_color = 0x07; // Light grey on black
    tty_clear();
}

void tty_clear(void) {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            VGA_BUFFER[y * VGA_WIDTH + x] = vga_entry(' ', tty_color);
        }
    }
}

void tty_putc(char c) {
    if (c == '\n') {
        tty_col = 0;
        tty_row++;
    } else {
        VGA_BUFFER[tty_row * VGA_WIDTH + tty_col] = vga_entry(c, tty_color);
        tty_col++;
    }

    if (tty_col >= VGA_WIDTH) {
        tty_col = 0;
        tty_row++;
    }

    if (tty_row >= VGA_HEIGHT) {
        // Scroll (simple version)
        for (int y = 0; y < VGA_HEIGHT - 1; y++) {
            for (int x = 0; x < VGA_WIDTH; x++) {
                VGA_BUFFER[y * VGA_WIDTH + x] = VGA_BUFFER[(y + 1) * VGA_WIDTH + x];
            }
        }
        for (int x = 0; x < VGA_WIDTH; x++) {
            VGA_BUFFER[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = vga_entry(' ', tty_color);
        }
        tty_row = VGA_HEIGHT - 1;
    }
}

void tty_puts(const char* str) {
    while (*str) {
        tty_putc(*str++);
    }
}

static void print_uint(uint64_t n, int base) {
    char buf[64];
    int i = 0;
    if (n == 0) {
        tty_putc('0');
        return;
    }
    while (n > 0) {
        int rem = n % base;
        buf[i++] = (rem < 10) ? (rem + '0') : (rem - 10 + 'a');
        n /= base;
    }
    while (--i >= 0) {
        tty_putc(buf[i]);
    }
}

void tty_printf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    for (const char* p = format; *p != '\0'; p++) {
        if (*p == '%') {
            p++;
            switch (*p) {
                case 's': tty_puts(va_arg(args, char*)); break;
                case 'c': tty_putc((char)va_arg(args, int)); break;
                case 'd': {
                    int n = va_arg(args, int);
                    if (n < 0) { tty_putc('-'); n = -n; }
                    print_uint(n, 10);
                    break;
                }
                case 'x': print_uint(va_arg(args, unsigned int), 16); break;
                case 'p': tty_puts("0x"); print_uint((uint64_t)va_arg(args, void*), 16); break;
                default: tty_putc(*p); break;
            }
        } else {
            tty_putc(*p);
        }
    }
    va_end(args);
}
