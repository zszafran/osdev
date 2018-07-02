#define ASM_FILE 1

#include <boot/registers.h>
#include <boot/mmu.h>
#include <kernel/kernel.h>

/* C symbol format. HAVE_ASM_USCORE is defined by configure. */
#ifdef HAVE_ASM_USCORE
# define EXT_C(sym)                     _ ## sym
#else
# define EXT_C(sym)                     sym
#endif

# Global Descriptor Table
.section .rodata
	.align 4

	gdt:
		.quad 0 # zero entry

	gdt_code_entry:
		.set gdt_code_seg, gdt_code_entry - gdt
		.word 0xffff			# segment limit first 0-15 bits
		.word 0x0					# base first 0-15 bits
		.byte 0x0					# base 16-23 bits
		.byte 0x9a				# access byte
		.byte 0xcf				# high 4 bits (flags) low 4 bits (limit 4 last bits)(limit is 20 bit wide)
		.byte 0x0					# base 24-31 bits

	gdt_data_entry:
		.set gdt_data_seg, gdt_data_entry - gdt
		.word 0xffff			# segment limit first 0-15 bits
		.word 0x0					# base first 0-15 bits
		.byte 0x0					# base 16-23 bits
		.byte 0x92				# access byte
		.byte 0xcf				# high 4 bits (flags) low 4 bits (limit 4 last bits)(limit is 20 bit wide)
		.byte 0x0					# base 24-31 bits

	gdt_pointer:
		.set gdt_limit, gdt_pointer - gdt - 1
		.word gdt_limit
		.long gdt

# The kernel entry point.
.section .text
	.global _start
	.type _start, @function
	.extern check_multiboot

	_start:
		movl %ebx, (multiboot_ptr)
		movl %eax, (multiboot_magic)

		movl $stack_top, %esp

		# Tests
		call check_multiboot
		# TODO: check PAE

		# load the GDT
    lgdt (gdt_pointer)
		jmp $0x08, $start

	start:
		# Setup segment selectors
		movw $0x10, %ax
		movw %ax, %ds
		movw %ax, %es
		movw %ax, %fs
		movw %ax, %gs
		movw %ax, %ss

		# Paging
		call setup_page_tables
		call enable_paging

		# Call the global constructors.
		call _init

		# Transfer control to the main kernel.
		call EXT_C(kmain)

		# Hang if kernel_main unexpectedly returns.
		jmp halt

	halt:
		cli
		hlt

		.hang:
			jmp .hang

	setup_page_tables:

		.recursive_map_page_directory_table:
			mov $page_directory_table, %eax
			orl $(MMU_PRESENT | MMU_WRITABLE), %eax
			movl %eax, (page_directory_table + 1023 * 8)

		.setup_page_directory_table:
			# map first directory entry to the page table
			mov $page_table, %eax
			orl $(MMU_PRESENT | MMU_WRITABLE), %eax
			mov %eax, (page_directory_table)

		.setup_page_table:
			# map each P2 entry to a huge 2MiB page
			mov $0, %ecx         # counter variable

			# identity map first 1G
			.identity_map_page_table:
				# map ecx-th P2 entry to a huge page that starts at address 2MiB*ecx
				mov %ecx, %eax
				imull $4096, %eax     # start address of ecx-th page
				orl $(MMU_PRESENT | MMU_WRITABLE), %eax
				movl %eax, page_table(, %ecx, 4) # map ecx-th entry

				inc %ecx              # increase counter
				cmp $1024, %ecx        # if counter == 512, the whole P2 table is mapped
				jne .identity_map_page_table  # else map the next entry

				ret

	enable_paging:
		# Set cr3 to the address of the page_directory_table.
		movl $page_directory_table, %eax
		movl %eax, %cr3

		# enable PAE-flag in cr4 (Physical Address Extension)
    # movl %cr4, %eax
    # orl $CR4_PHYSICAL_ADDRESS_EXTENSION, %eax
    # mov %eax, %cr4

		# Enable paging and the write-protect bit.
		movl %cr0, %eax
		orl $(CR0_WRITE_PROTECT | CR0_PAGING_ENABLE), %eax
		movl %eax, %cr0
		ret

	.size _start, . - _start

# Multiboot info pointer
.section .data.multiboot_info
	.global multiboot_ptr
	.global multiboot_magic

	multiboot_ptr:
		.align 4
		.long 0

	multiboot_magic:
		.align 4
		.long 0

# Reserve a stack for the initial thread.
.section .bss
	.align 4096

	page_directory_table:
		.rept 4096
			.byte 0
		.endr
		.align 4096

	page_table:
		.rept 4096
			.byte 0
		.endr
		.align 4096

	stack_bottom:
		.skip 4096 * 4 # 16 KiB

	stack_top: