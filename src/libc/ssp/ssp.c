#include <stdint.h>
#include <stdlib.h>
#include <ssp.h>

#ifndef STACK_CHK_GUARD
#if UINT32_MAX == UINTPTR_MAX
#define STACK_CHK_GUARD 0xe2dee396
#else
#define STACK_CHK_GUARD 0x595e9fbd94fda766
#endif
#endif

//uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

__attribute__((noreturn)) void __stack_chk_fail(void)
{
  //	asm volatile ("mov [753665],195h"::);
  //	asm volatile ("mov [753665],33h"::);
  *((uint8_t *)0xB8000) = '!';
  *((uint8_t *)0xB8001) = 79;
  *((uint8_t *)0xB8002) = 'S';
  *((uint8_t *)0xB8003) = 79;
  *((uint8_t *)0xB8004) = 't';
  *((uint8_t *)0xB8005) = 79;
  *((uint8_t *)0xB8006) = 'a';
  *((uint8_t *)0xB8007) = 79;
  *((uint8_t *)0xB8008) = 'c';
  *((uint8_t *)0xB8009) = 79;
  *((uint8_t *)0xB800A) = 'k';
  *((uint8_t *)0xB800B) = 79;
  *((uint8_t *)0xB800C) = ' ';
  *((uint8_t *)0xB800D) = 79;
  *((uint8_t *)0xB800E) = 's';
  *((uint8_t *)0xB800F) = 79;
  *((uint8_t *)0xB8010) = 'm';
  *((uint8_t *)0xB8011) = 79;
  *((uint8_t *)0xB8012) = 'a';
  *((uint8_t *)0xB8013) = 79;
  *((uint8_t *)0xB8014) = 's';
  *((uint8_t *)0xB8015) = 79;
  *((uint8_t *)0xB8016) = 'h';
  *((uint8_t *)0xB8017) = 79;
  *((uint8_t *)0xB8018) = 'i';
  *((uint8_t *)0xB8019) = 79;
  *((uint8_t *)0xB801A) = 'n';
  *((uint8_t *)0xB801B) = 79;
  *((uint8_t *)0xB801C) = 'g';
  *((uint8_t *)0xB801D) = 79;
  *((uint8_t *)0xB801E) = ' ';
  *((uint8_t *)0xB801F) = 79;
  *((uint8_t *)0xB8020) = 'd';
  *((uint8_t *)0xB8021) = 79;
  *((uint8_t *)0xB8022) = 'e';
  *((uint8_t *)0xB8023) = 79;
  *((uint8_t *)0xB8024) = 't';
  *((uint8_t *)0xB8025) = 79;
  *((uint8_t *)0xB8026) = 'e';
  *((uint8_t *)0xB8027) = 79;
  *((uint8_t *)0xB8028) = 'c';
  *((uint8_t *)0xB8029) = 79;
  *((uint8_t *)0xB802A) = 't';
  *((uint8_t *)0xB802B) = 79;
  *((uint8_t *)0xB802C) = 'e';
  *((uint8_t *)0xB802D) = 79;
  *((uint8_t *)0xB802E) = 'd';
  *((uint8_t *)0xB802F) = 79;
  *((uint8_t *)0xB8030) = '!';
  *((uint8_t *)0xB8031) = 79;
  *((uint8_t *)0xB8032) = 'S';
  *((uint8_t *)0xB8033) = 79;
  *((uint8_t *)0xB8034) = 'y';
  *((uint8_t *)0xB8035) = 79;
  *((uint8_t *)0xB8036) = 's';
  *((uint8_t *)0xB8037) = 79;
  *((uint8_t *)0xB8038) = 't';
  *((uint8_t *)0xB8039) = 79;
  *((uint8_t *)0xB803A) = 'e';
  *((uint8_t *)0xB803B) = 79;
  *((uint8_t *)0xB803C) = 'm';
  *((uint8_t *)0xB803D) = 79;
  *((uint8_t *)0xB803E) = ' ';
  *((uint8_t *)0xB803F) = 79;
  *((uint8_t *)0xB8040) = 'h';
  *((uint8_t *)0xB8041) = 79;
  *((uint8_t *)0xB8042) = 'a';
  *((uint8_t *)0xB8043) = 79;
  *((uint8_t *)0xB8044) = 'l';
  *((uint8_t *)0xB8045) = 79;
  *((uint8_t *)0xB8046) = 't';
  *((uint8_t *)0xB8047) = 79;
  *((uint8_t *)0xB8048) = 'e';
  *((uint8_t *)0xB8049) = 79;
  *((uint8_t *)0xB804A) = 'd';
  *((uint8_t *)0xB804B) = 79;
  asm volatile("cli" ::);
  asm volatile("hlt" ::);
#if __STDC_HOSTED__
  //	asm volatile("cli"::);
  //	asm volatile("hlt"::);
  abort();
#elif __is_libk
  //	asm volatile("cli"::);
  //	asm volatile("hlt"::);
  panic("stack smashing detected");
  epanic();
  asm volatile("cli" ::);
  asm volatile("hlt" ::);
  __builtin_unreachable();
#endif
}