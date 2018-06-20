/* C symbol format. HAVE_ASM_USCORE is defined by configure. */
#ifdef HAVE_ASM_USCORE
# define EXT_C(sym)                     _ ## sym
#else
# define EXT_C(sym)                     sym
#endif

# The kernel entry point.
.section .text
	.global _start
  .code32
	.type _start, @function
	.extern kmain
	_start:
		movl $stack_top, %esp

		# Reset EFLAGS.
		pushl $0
		popf

		# Push the pointer to the Multiboot information structure.
		pushl %ebx
		# Push the magic value.
		pushl %eax

		# Tests
		call check_multiboot
		call check_cpuid
		call check_extended_cpuid
		call check_long_mode

		# Call the global constructors.
		# call _init

		# Transfer control to the main kernel.
		call EXT_C(kmain)
		# movl $0x2f4b2f4f, (0xb8000)

		# Hang if kernel_main unexpectedly returns.
		cli
	1:	hlt
		jmp 1b

	clear_screen:
		mov $0xB8000, %edi
		mov $0x0F000F00, %eax
		mov $1000, %ecx
		rep stosl
	
	# Prints `ERR: ` and the given error code to screen and hangs.
	# parameter: error code (in ascii) in al
	error:
    movl $0x4f524f45, (0xb8000)
    movl $0x4f3a4f52, (0xb8004)
    movl $0x4f204f20, (0xb8008)
    movb %al, (0xb800a)
    hlt

	check_multiboot:
    cmpl $0x36d76289, %eax
    jne .no_multiboot
    ret

	.no_multiboot:
		movb $'0', %al
		jmp error

	check_cpuid:
    # Check if CPUID is supported by attempting to flip the ID bit (bit 21)
    # in the FLAGS register. If we can flip it, CPUID is available.

    # Copy FLAGS in to EAX via stack
    pushfl
    pop %eax

    # Copy to ECX as well for comparing later on
    mov %eax, %ecx

    # Flip the ID bit
    xor $0x200000, %eax

    # Copy EAX to FLAGS via the stack
    push %eax
    popfl

    # Copy FLAGS back to EAX (with the flipped bit if CPUID is supported)
    pushfl
    pop %eax

    # Restore FLAGS from the old version stored in ECX (i.e. flipping the
    # ID bit back if it was ever flipped).
    push %ecx
    popfl

    # Compare EAX and ECX. If they are equal then that means the bit
    # wasn't flipped, and CPUID isn't supported.
    xor %ecx, %eax
    jz .no_cpuid
    ret

	.no_cpuid:
    movb $'1', %al
    jmp error

	check_extended_cpuid:
    # test if extended processor info in available
    mov $0x80000000, %eax    # implicit argument for cpuid
    cpuid                    # get highest supported argument
    cmp $0x80000001, %eax    # it needs to be at least 0x80000001
    jb .no_extended_cpuid    # if it's less, the CPU is too old for long mode
		ret

	.no_extended_cpuid:
		mov $'2', %al
		jmp error

	check_long_mode:
    # use extended info to test if long mode is available
    mov $0x80000001, %eax   # argument for extended processor info
    cpuid                   # returns various feature bits in ecx and edx
    test $0x20000000, %edx  # test if the LM-bit is set in the D-register
    jz .no_long_mode        # If it's not set, there is no long mode
    ret

	.no_long_mode:
		mov $'3', %al
		jmp error

	.size _start, . - _start

# Reserve a stack for the initial thread.
.section .bss
	.align 16
	stack_bottom:
		.skip 16384 # 16 KiB
	stack_top:
