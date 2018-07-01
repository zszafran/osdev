#pragma once

#define GDT_DESCRIPTOR (1ull << 44)
#define GDT_PRESENT (1ull << 47)
#define GDT_READWRITE (1ull << 41)
#define GDT_EXECUTABLE (1ull << 43)
#define GDT_64BIT (1ull << 53)
#define GDT_TSS (9ull << 40)