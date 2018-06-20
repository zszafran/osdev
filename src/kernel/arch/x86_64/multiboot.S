#define ASM_FILE        1
#include <boot/multiboot2.h>

/*  The flags for the Multiboot header. */
#ifdef __ELF__
# define AOUT_KLUDGE 0
#else
# define AOUT_KLUDGE MULTIBOOT_AOUT_KLUDGE
#endif

.section .multiboot
  .code32
  .align 8
  multiboot_header_start:
    /*  magic */
    .long   MULTIBOOT2_HEADER_MAGIC
    /*  ISA: i386 */
    .long   MULTIBOOT_ARCHITECTURE_I386
    /*  Header length. */
    .long   multiboot_header_end - multiboot_header_start
    /*  checksum */
    .long   -(MULTIBOOT2_HEADER_MAGIC + MULTIBOOT_ARCHITECTURE_I386 + (multiboot_header_end - multiboot_header_start))

    .short MULTIBOOT_HEADER_TAG_END
    .short 0
    .long 8
  multiboot_header_end: