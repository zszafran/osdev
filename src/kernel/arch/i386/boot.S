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

		# Call the global constructors.
		call _init

		# Transfer control to the main kernel.
		call EXT_C(kmain)

		# Hang if kernel_main unexpectedly returns.
		cli
	1:	hlt
		jmp 1b

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
	.align 16

	stack_bottom:
		.skip 4096 * 4 # 16 KiB

	stack_top: