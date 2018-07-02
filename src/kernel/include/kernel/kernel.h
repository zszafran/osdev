#pragma once

#define KERNEL_PHYSICAL_OFFSET 0x40000000
#define KERNEL_PHYSICAL_ADDR 0x100000

#define KERNEL_VIRTUAL_OFFSET 0xC0000000
#define KERNEL_VIRTUAL_ADDR KERNEL_PHYSICAL_ADDR + KERNEL_VIRTUAL_OFFSET

#define VIRT_TO_PHYS_ADDR(addr) ((addr)-KERNEL_VIRTUAL_OFFSET)
#define PHYS_TO_VIRT_ADDR(addr) ((addr) + KERNEL_VIRTUAL_OFFSET)