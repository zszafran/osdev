#include <kernel/section.h>
#include <kernel/log.h>

typedef void (*ctor_func)(void);

void init_ctors()
{
  log("Calling global constructors @ 0x%x...", SECTION_CTORS_START);
  for (ctor_func *ctor = (ctor_func *)SECTION_CTORS_START; *ctor; ++ctor)
  {
    debug("\t0x%x --> 0x%x", ctor, *ctor);
    (*ctor)();
  }
}