#pragma once

#include <sys/cdefs.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

  void halt(void);
  __attribute__((__noreturn__)) void abort(void);
  __attribute__((__noreturn__)) void panic(string_t);
  __attribute__((__noreturn__)) void epanic();
  char *itoa(int value, char *string, int radix);

#ifdef __cplusplus
}
#endif
