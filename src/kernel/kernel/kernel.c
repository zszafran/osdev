#include <stdio.h>
#include <stdint.h>

#include <kernel/tty.h>
#include <kernel/log.h>
#include <boot/info.h>

boot_info_t boot_info;

void kmain()
{
  read_multiboot(&boot_info);

  terminal_initialize(
      boot_info.framebuffer_tag->common.framebuffer_addr,
      boot_info.framebuffer_tag->common.framebuffer_width,
      boot_info.framebuffer_tag->common.framebuffer_height);

  log("Booting...");

  print_boot_info(&boot_info);

  debug("Hello, kernel World!");
}