#pragma once

#define CR0_PROTECTED_MODE_ENABLED (1 << 0)
#define CR0_EXTENSION_TYPE (1 << 4)
#define CR0_WRITE_PROTECT (1 << 16)
#define CR0_PAGING_ENABLE (1 << 31)

#define CR4_PAGE_SIZE_EXTENSION (1 << 4)
#define CR4_PHYSICAL_ADDRESS_EXTENSION (1 << 5)

#define MSR_LONG_MODE (1 << 8)