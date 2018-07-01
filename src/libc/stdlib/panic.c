#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void halt(void)
{
  asm volatile("cli\n" ::);
  asm volatile("hlt\n" ::);
}

#if defined(__is_libk) // Disable panic() function if it is not part of kernel

void panic(string_t reason)
{
  printf("\nKernel panic: %s\n", reason);
  halt();
  while (1)
  {
  }
  __builtin_unreachable();
}

void epanic()
{
  *((uint8_t *)0xB8000) = '!';
  *((uint8_t *)0xB8001) = 79;
  *((uint8_t *)0xB8002) = 'K';
  *((uint8_t *)0xB8003) = 79;
  *((uint8_t *)0xB8004) = 'e';
  *((uint8_t *)0xB8005) = 79;
  *((uint8_t *)0xB8006) = 'r';
  *((uint8_t *)0xB8007) = 79;
  *((uint8_t *)0xB8008) = 'n';
  *((uint8_t *)0xB8009) = 79;
  *((uint8_t *)0xB800A) = 'e';
  *((uint8_t *)0xB800B) = 79;
  *((uint8_t *)0xB800C) = 'l';
  *((uint8_t *)0xB800D) = 79;
  *((uint8_t *)0xB800E) = ' ';
  *((uint8_t *)0xB800F) = 79;
  *((uint8_t *)0xB8010) = 'p';
  *((uint8_t *)0xB8011) = 79;
  *((uint8_t *)0xB8012) = 'a';
  *((uint8_t *)0xB8013) = 79;
  *((uint8_t *)0xB8014) = 'n';
  *((uint8_t *)0xB8015) = 79;
  *((uint8_t *)0xB8016) = 'i';
  *((uint8_t *)0xB8017) = 79;
  *((uint8_t *)0xB8018) = 'c';
  *((uint8_t *)0xB8019) = 79;
  halt();
  while (1)
  {
  }
  __builtin_unreachable();
}
#endif