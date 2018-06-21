#include <stdio.h>
#include <stdint.h>

#include <kernel/tty.h>
#include <kernel/log.h>
#include <boot/info.h>

extern uint32_t multiboot_ptr;
extern uint32_t multiboot_magic;

void kmain()
{
  terminal_initialize();

  log("Booting...");

  print_multiboot(multiboot_magic, multiboot_ptr);

  debug("Hello, kernel World!");
}