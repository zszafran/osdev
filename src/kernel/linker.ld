ENTRY(_start)

#include <kernel/kernel.h>

#define SECTION(name) \
    name BLOCK(4K) : ALIGN(4K)

#define DEFINE_START(name) \
    _##name##_START = ABSOLUTE(.);

#define DEFINE_END(name) \
    _##name##_SIZE = ABSOLUTE(.) - _##name##_START;

SECTIONS
{
	. = KERNEL_PHYSICAL_ADDR;

	DEFINE_START(KERNEL)

	SECTION(.text)
	{
		DEFINE_START(TEXT)
		KEEP(*(.multiboot))
		*(.text .text.*)
		*(.rodata .rodata.*)
		*(.data.rel.ro.local*) *(.data.rel.ro .data.rel.ro.*)
		DEFINE_END(TEXT)
	}

	SECTION(.data)
	{
		DEFINE_START(DATA)
		*(.data .data.*)
		DEFINE_START(CTORS)
    *(.ctor*)
		LONG(0)
    DEFINE_END(CTORS)
		DEFINE_END(DATA)
	}

	SECTION(.bss)
	{
		DEFINE_START(BBS)
		*(COMMON)
		*(.bss .bss.*)
		DEFINE_END(BBS)
	}

	DEFINE_END(KERNEL)
}
