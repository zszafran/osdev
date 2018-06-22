#pragma once

#include <stdint.h>
#include <boot/multiboot2.h>

typedef struct boot_info
{
  uint32_t size;

  uintptr_t kernel_start;
  uintptr_t kernel_end;

  uintptr_t multiboot_start;
  uintptr_t multiboot_end;

  struct multiboot_tag_string *command_line_tag;
  struct multiboot_tag_string *boot_loader_name_tag;
  struct multiboot_tag_basic_meminfo *basic_meminfo_tag;
  struct multiboot_tag_bootdev *boot_device_tag;
  struct multiboot_tag_mmap *memory_map_tag;
  struct multiboot_tag_new_acpi *new_acpi_tag;
  struct multiboot_tag_old_acpi *old_acpi_tag;
  struct multiboot_tag_smbios *smbios_tag;
  struct multiboot_tag_elf_sections *elf_sections_tag;
  struct multiboot_tag_module *module_tag;
  struct multiboot_tag_framebuffer *framebuffer_tag;
  struct multiboot_tag *end_tag;
} boot_info_t;

void read_multiboot(boot_info_t *self);
void print_boot_info(boot_info_t *self);