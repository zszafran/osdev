#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int printf(const char *restrict format, ...)
{
  va_list parameters;
  va_start(parameters, format);
  int written = vprintf(format, parameters);
  va_end(parameters);
  return written;
}
