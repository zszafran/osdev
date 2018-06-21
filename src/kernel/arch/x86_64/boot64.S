/* C symbol format. HAVE_ASM_USCORE is defined by configure. */
#ifdef HAVE_ASM_USCORE
# define EXT_C(sym)                     _ ## sym
#else
# define EXT_C(sym)                     sym
#endif

.code64

.section .text
	.global _start64
	.type _start64, @function
  .extern kmain

	_start64:
		# Setup segment selectors
		movw $0, %ax
		movw %ax, %ds
		movw %ax, %es
		movw %ax, %fs
		movw %ax, %gs
		movw %ax, %ss

		# Call the global constructors.
		call _init

		# Transfer control to the main kernel.
		call EXT_C(kmain)
		# movq $0x2f592f412f4b2f4f, %rax
		# movq %rax, (0xb8000)

		# Hang if kernel_main unexpectedly returns.
		cli
    hlt
	1:
		jmp 1b