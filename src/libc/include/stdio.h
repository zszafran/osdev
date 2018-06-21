#pragma once

#include <stdarg.h>
#include <sys/cdefs.h>
#include <string.h>
#include <stdbool.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C"
{
#endif

  bool print(const char *data, size_t length);
  int printf(const char *__restrict, ...);
  int putchar(int);
  int puts(const char *);
  int vprintf(const char *__restrict format, va_list parameters);

#ifdef __cplusplus
}
#endif
