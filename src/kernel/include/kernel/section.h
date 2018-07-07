#pragma once

#include <stdint.h>

extern char _KERNEL_START[];
extern char _KERNEL_SIZE[];
#define SECTION_KERNEL_START ((uintptr_t)_KERNEL_START)
#define SECTION_KERNEL_SIZE ((uintptr_t)_KERNEL_SIZE)

extern char _TEXT_START[];
extern char _TEXT_SIZE[];
#define SECTION_TEXT_START ((uintptr_t)_TEXT_START)
#define SECTION_TEXT_SIZE ((uintptr_t)_TEXT_SIZE)

extern char _DATA_START[];
extern char _DATA_SIZE[];
#define SECTION_DATA_START ((uintptr_t)_DATA_START)
#define SECTION_DATA_SIZE ((uintptr_t)_DATA_SIZE)

extern char _BBS_START[];
extern char _BBS_SIZE[];
#define SECTION_BBS_START ((uintptr_t)_BBS_START)
#define SECTION_BBS_SIZE ((uintptr_t)_BBS_SIZE)

extern char _CTORS_START[];
extern char _CTORS_SIZE[];
#define SECTION_CTORS_START ((uintptr_t)_CTORS_START)
#define SECTION_CTORS_SIZE ((uintptr_t)_CTORS_SIZE)