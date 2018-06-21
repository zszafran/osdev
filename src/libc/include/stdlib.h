#pragma once

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C"
{
#endif

  __attribute__((__noreturn__)) void abort(void);
  char *itoa(int value, char *string, int radix);

#ifdef __cplusplus
}
#endif
