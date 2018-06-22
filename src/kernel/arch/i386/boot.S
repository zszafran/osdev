/* C symbol format. HAVE_ASM_USCORE is defined by configure. */
#ifdef HAVE_ASM_USCORE
# define EXT_C(sym)                     _ ## sym
#else
# define EXT_C(sym)                     sym
#endif

# The kernel entry point.
.section .text
	.global _start
	.type _start, @function
	.extern check_multiboot

	_start:
		movl $stack_top, %esp

		# Reset EFLAGS.
		pushl $0
		popf

		movl %ebx, (multiboot_ptr)
		movl %eax, (multiboot_magic)

		# Tests
		call check_multiboot

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
		ret

	enable_paging:
		# Set cr3 to the address of the page_directory_table.
		movl $page_directory_table, %ecx
		movl %ecx, %cr3

		# Enable paging and the write-protect bit.
		movl %cr0, %ecx
		orl $1 << 31, %eax
		movl %ecx, %cr0
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
		.skip 4096

	paget_table:
		.skip 4096

	stack_bottom:
		.skip 4096 * 4 # 16 KiB

	stack_top: