/* C symbol format. HAVE_ASM_USCORE is defined by configure. */
#ifdef HAVE_ASM_USCORE
# define EXT_C(sym)                     _ ## sym
#else
# define EXT_C(sym)                     sym
#endif

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

	/* Reset EFLAGS. */
	pushl $0
	popf

	/* Push the pointer to the Multiboot information structure. */
	pushl %ebx
	/* Push the magic value. */
	pushl %eax

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call EXT_C(kmain)

	# Hang if kernel_main unexpectedly returns.
	cli
1:	hlt
	jmp 1b
.size _start, . - _start
