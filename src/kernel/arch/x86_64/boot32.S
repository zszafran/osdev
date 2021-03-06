#define ASM_FILE 1

#include <boot/registers.h>
#include <boot/mmu.h>
#include <boot/gdt.h>
#include <kernel/kernel.h>

/* C symbol format. HAVE_ASM_USCORE is defined by configure. */
#ifdef HAVE_ASM_USCORE
# define EXT_C(sym)                     _ ## sym
#else
# define EXT_C(sym)                     sym
#endif

.code32

# Global Descriptor Table
.section .rodata
	.align 4

	gdt64:
		.quad 0 # zero entry

	gdt64_code_entry:
		.set gdt64_code_seg, gdt64_code_entry - gdt64
		.quad GDT_DESCRIPTOR | GDT_PRESENT | GDT_READWRITE | GDT_EXECUTABLE | GDT_64BIT

	gdt64_data_entry:
		.set gdt64_data_seg, gdt64_data_entry - gdt64
		.quad GDT_DESCRIPTOR | GDT_PRESENT | GDT_READWRITE

	gdt64_pointer:
		.set gdt64_limit, gdt64_pointer - gdt64 - 1
		.word gdt64_limit
		.quad gdt64

# The kernel entry point.
.section .text
	.global _start
	.type _start, @function
	.extern _start64
	.extern check_multiboot
	.extern check_cpuid
	.extern check_extended_cpuid
	.extern check_long_mode
	.extern check_sse

	_start:
		movl %ebx, (multiboot_ptr)
		movl %eax, (multiboot_magic)

		movl $stack_top, %esp

		# Tests
		call check_multiboot
		call check_cpuid
		call check_extended_cpuid
		call check_long_mode
		call check_sse
		# TODO: check PAE

		# Paging
		call setup_page_tables
    call enable_paging

		# load the 64-bit GDT
    lgdt (gdt64_pointer)

		# Long jump to 64-bit code
		ljmp $gdt64_code_seg, $_start64

	setup_page_tables:

		.recursive_map_level4_table:
			# recursive map P4
			mov $page_map_level4_table, %eax
			orl $(MMU_PRESENT | MMU_WRITABLE), %eax
			movl %eax, (page_map_level4_table + 511 * 8)

		.setup_page_map_level4_table:
			# map first P4 entry to P3 table
			mov $page_directory_pointer_table, %eax
			orl $(MMU_PRESENT | MMU_WRITABLE), %eax
			movl %eax, (page_map_level4_table)

		.setup_page_directory_pointer_table:
			# map first P3 entry to P2 table
			movl $page_directory_table, %eax
			orl $(MMU_PRESENT | MMU_WRITABLE), %eax
			mov %eax, (page_directory_pointer_table)

		.setup_page_directory_table:
			# map each P2 entry to a huge 2MiB page
			mov $0, %ecx         # counter variable

			# identity map first 1G
			.identity_map_page_directory_table:
				# map ecx-th P2 entry to a huge page that starts at address 2MiB*ecx
				movl 0x200000, %eax   # 2MiB
				mul %ecx              # start address of ecx-th page
				orl $(MMU_PRESENT | MMU_WRITABLE | MMU_HUGE), %eax
				movl %eax, page_directory_table(, %ecx, 8) # map ecx-th entry

				inc %ecx              # increase counter
				cmp $512, %ecx        # if counter == 512, the whole P2 table is mapped
				jne .identity_map_page_directory_table  # else map the next entry

				ret

	enable_paging:
		# load P4 to cr3 register (cpu uses this to access the P4 table)
    movl $page_map_level4_table, %eax
    movl %eax, %cr3

    # enable PAE-flag in cr4 (Physical Address Extension)
    movl %cr4, %eax
    orl $CR4_PHYSICAL_ADDRESS_EXTENSION, %eax
    mov %eax, %cr4

    # set the long mode bit in the EFER MSR (model specific register)
    mov $0xC0000080, %ecx
    rdmsr
    orl $MSR_LONG_MODE, %eax
    wrmsr

    # enable paging in the cr0 register
    movl %cr0, %eax
    orl $(CR0_WRITE_PROTECT | CR0_PAGING_ENABLE), %eax
    mov %eax, %cr0

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

	page_map_level4_table:					# P4
    .rept 4096
			.byte 0
		.endr
		.align 4096

	page_directory_pointer_table:		# P2
		.rept 4096
			.byte 0
		.endr
		.align 4096

	page_directory_table:						# P3
		.rept 4096
			.byte 0
		.endr
		.align 4096

	stack_bottom:
		.skip 4096 * 4

	stack_top: