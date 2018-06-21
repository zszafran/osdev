#pragma once

#include <stddef.h>

void terminal_initialize(unsigned long long framebuffer_addr,
                         unsigned int width,
                         unsigned int height);
void terminal_clear(void);
void terminal_putchar(char c);
void terminal_write(const char *data, size_t size);
void terminal_writestring(const char *data);
