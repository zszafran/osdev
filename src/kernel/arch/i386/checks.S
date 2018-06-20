.section .text
  .global check_multiboot

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