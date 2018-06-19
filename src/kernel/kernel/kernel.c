#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/log.h>
#include <boot/info.h>

void kmain(unsigned long magic, unsigned long addr)
{
  terminal_initialize();

  //printf("\033[91mK\033[92me\033[93mr\033[94mn\033[95me\033[96ml booting...\033[0m\n");
  log("Booting...");

  print_multiboot(magic, addr);

  debug("Hello, kernel World!");
}