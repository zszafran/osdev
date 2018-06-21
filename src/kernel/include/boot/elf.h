#pragma once

#include <stdint.h>

#ifdef __i386__
typedef struct elf_section
{
  uint32_t name;
  uint32_t type;
  uint32_t flags;
  uint32_t addr;
  uint32_t offset;
  uint32_t size;
  uint32_t link;
  uint32_t info;
  uint32_t addralign;
  uint32_t entry_size;
} elf_section_t;
#endif

#ifdef __x86_64__
typedef struct elf_section
{
  uint32_t name;
  uint32_t type;
  uint64_t flags;
  uint64_t addr;
  uint64_t offset;
  uint64_t size;
  uint32_t link;
  uint32_t info;
  uint64_t addralign;
  uint64_t entry_size;
} elf_section_t;
#endif
