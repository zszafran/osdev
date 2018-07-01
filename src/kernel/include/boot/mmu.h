#pragma once

#define MMU_PRESENT (1 << 0)
#define MMU_WRITABLE (1 << 1)
#define MMU_USER_MEMORY (1 << 2)
#define MMU_WRITE_THROUGH (1 << 3)
#define MMU_CACHE_DISABLED (1 << 4)
#define MMU_ACCESSED (1 << 5)
#define MMU_DIRTY (1 << 6)
#define MMU_HUGE (1 << 7)
#define MMU_GLOBAL (1 << 8)