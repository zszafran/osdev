#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int get_int_len(int value)
{
  int l = !value;
  while (value)
  {
    l++;
    value /= 10;
  }
  return l;
}

int vprintf(const char *restrict format, va_list parameters)
{
  int written = 0;

  while (*format != '\0')
  {
    size_t maxrem = INT_MAX - written;

    if (format[0] != '%' || format[1] == '%')
    {
      if (format[0] == '%')
        format++;
      size_t amount = 1;
      while (format[amount] && format[amount] != '%')
        amount++;
      if (maxrem < amount)
      {
        // TODO: Set errno to EOVERFLOW.
        return -1;
      }
      if (!print(format, amount))
        return -1;
      format += amount;
      written += amount;
      continue;
    }

    const char *format_begun_at = format++;

    if (*format == 'c')
    {
      format++;
      char c = (char)va_arg(parameters, int /* char promotes to int */);
      if (!maxrem)
      {
        // TODO: Set errno to EOVERFLOW.
        return -1;
      }
      if (!print(&c, sizeof(c)))
        return -1;
      written++;
    }
    else if (*format == 's')
    {
      format++;
      const char *str = va_arg(parameters, const char *);
      size_t len = strlen(str);
      if (maxrem < len)
      {
        // TODO: Set errno to EOVERFLOW.
        return -1;
      }
      if (!print(str, len))
        return -1;
      written += len;
    }
    else if (*format == 'd')
    {
      format++;
      int num = va_arg(parameters, int);
      size_t len = get_int_len(num);
      char str[len];
      itoa(num, str, 10);
      if (!print(str, len))
        return -1;
      written += len;
    }
    else if (*format == 'u')
    {
      format++;
      int num = va_arg(parameters, int);
      size_t len = get_int_len(num);
      char str[len];
      itoa(num, str, 10);
      if (!print(str, len))
        return -1;
      written += len;
    }
    else if (*format == 'x')
    {
      format++;
      int num = va_arg(parameters, int);
      size_t len = get_int_len(num);
      char str[len];
      itoa(num, str, 16);
      if (!print(str, len))
        return -1;
      written += len;
    }
    else
    {
      format = format_begun_at;
      size_t len = strlen(format);
      if (maxrem < len)
      {
        // TODO: Set errno to EOVERFLOW.
        return -1;
      }
      if (!print(format, len))
        return -1;
      written += len;
      format += len;
    }
  }

  return written;
}
