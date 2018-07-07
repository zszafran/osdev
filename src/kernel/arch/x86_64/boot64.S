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

		# OKAY means we are in full long mode
		movq	$0x2f592f412f4b2f4f, %rax
		movq	%rax, (0xb8000)

		# Transfer control to the main kernel.
		call EXT_C(kmain)
		
		# Returned from main
		movq $0x2f542f4c2f412f48, %rax
		movq %rax, (0xb8f98)

		# Hang if kernel_main unexpectedly returns.
		jmp halt

	halt:
		cli
		hlt

		.hang:
			jmp .hang