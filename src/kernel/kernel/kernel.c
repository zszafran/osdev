#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/log.h>
#include <boot/info.h>

void kmain(unsigned long magic, unsigned long addr)
{
  terminal_initialize();

  log("Booting...");

  print_multiboot(magic, addr);

  debug("Hello, kernel World!");
}