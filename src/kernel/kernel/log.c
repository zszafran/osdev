#include <stdarg.h>
#include <stdio.h>

void log(const char *restrict format, ...)
{
  printf("\033[92m>>\033[0m ");
  va_list parameters;
  va_start(parameters, format);
  vprintf(format, parameters);
  va_end(parameters);
  printf("\n");
}

void warn(const char *restrict format, ...)
{
  printf("\033[93m>>\033[0m ");
  va_list parameters;
  va_start(parameters, format);
  vprintf(format, parameters);
  va_end(parameters);
  printf("\n");
}

void error(const char *restrict format, ...)
{
  printf("\033[91m>>\033[0m ");
  va_list parameters;
  va_start(parameters, format);
  vprintf(format, parameters);
  va_end(parameters);
  printf("\n");
}

void debug(const char *restrict format, ...)
{
  printf("\033[94m>>\033[0m ");
  va_list parameters;
  va_start(parameters, format);
  vprintf(format, parameters);
  va_end(parameters);
  printf("\n");
}