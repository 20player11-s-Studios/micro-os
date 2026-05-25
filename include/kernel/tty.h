#ifndef TTY_H
#define TTY_H

#include <stddef.h>
#include <stdint.h>

void tty_init(void);
void tty_putc(char c);
void tty_puts(const char* str);
void tty_printf(const char* format, ...);
void tty_set_color(uint8_t fg, uint8_t bg);
void tty_clear(void);

#endif
