/* The bootloader will look at this image and start execution at the symbol
   designated at the entry point. */
ENTRY(_start)

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
	/* Begin putting sections at 1 MiB, a conventional place for kernels to be
	   loaded at by the bootloader. */
	. = 1M;

	/* First put the multiboot header, as it is required to be put very early
	   early in the image or the bootloader won't recognize the file format.
	   Next we'll put the .text section. */
	.boot BLOCK(4K) : ALIGN(4K)
	{
		KEEP(*(.multiboot))
	}

	/* Text data. */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.text .text.*)
	}

	/* Read-only data. */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
			*(.rodata .rodata.*)
	}

	/* Read-only data. */
	.data.rel.ro BLOCK(4K) : ALIGN(4K)
	{
			*(.data.rel.ro.local*) *(.data.rel.ro .data.rel.ro.*)
	}

	/* Read-write data (initialized) */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data .data.*)
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss .bss.*)
	}

	/* The compiler may produce other sections, put them in the proper place in
	   in this file, if you'd like to include them in the final kernel. */
}
