#include <stdio.h>
#include <stdint.h>
#include <boot/multiboot2.h>
#include <boot/elf.h>
#include <boot/info.h>
#include <kernel/log.h>

extern const uint32_t multiboot_ptr;
extern const uint32_t multiboot_magic;

void read_multiboot(boot_info_t *self)
{
  if (multiboot_magic != MULTIBOOT2_BOOTLOADER_MAGIC)
  {
    error("Invalid magic number: 0x%x", multiboot_magic);
    return;
  }

  if (multiboot_ptr & 7)
  {
    error("Unaligned mbi: 0x%x", multiboot_ptr);
    return;
  }

  self->multiboot_start = multiboot_ptr;

  // skip 8 because the magic number is stored there
  struct multiboot_tag *tag = (struct multiboot_tag *)((uintptr_t)(multiboot_ptr + 8));

  while (tag->type != MULTIBOOT_TAG_TYPE_END)
  {
    switch (tag->type)
    {
    case MULTIBOOT_TAG_TYPE_CMDLINE:
      self->command_line_tag = (struct multiboot_tag_string *)tag;
      break;

    case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
      self->boot_loader_name_tag = (struct multiboot_tag_string *)tag;
      break;

    case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
      self->basic_meminfo_tag = (struct multiboot_tag_basic_meminfo *)tag;
      break;

    case MULTIBOOT_TAG_TYPE_BOOTDEV:
      self->boot_device_tag = (struct multiboot_tag_bootdev *)tag;
      break;

    case MULTIBOOT_TAG_TYPE_MMAP:
      self->memory_map_tag = (struct multiboot_tag_mmap *)tag;
      break;

    case MULTIBOOT_TAG_TYPE_ACPI_NEW:
      self->new_acpi_tag = (struct multiboot_tag_new_acpi *)tag;
      break;

    case MULTIBOOT_TAG_TYPE_ACPI_OLD:
      self->old_acpi_tag = (struct multiboot_tag_old_acpi *)tag;
      break;

    case MULTIBOOT_TAG_TYPE_SMBIOS:
      self->smbios_tag = (struct multiboot_tag_smbios *)tag;
      break;

    case MULTIBOOT_TAG_TYPE_ELF_SECTIONS:
      self->elf_sections_tag = (struct multiboot_tag_elf_sections *)tag;
      break;

    case MULTIBOOT_TAG_TYPE_FRAMEBUFFER:
      self->framebuffer_tag = (struct multiboot_tag_framebuffer *)tag;

    case MULTIBOOT_TAG_TYPE_MODULE:
      self->module_tag = (struct multiboot_tag_module *)tag;
    }

    tag = (struct multiboot_tag *)((uint8_t *)tag + ((tag->size + 7) & ~7));
  }

  if (self->elf_sections_tag)
  {
    elf_section_t *section;
    for (uintptr_t i = 1; i < self->elf_sections_tag->num; i++)
    {
      section = (elf_section_t *)(self->elf_sections_tag->sections + self->elf_sections_tag->entsize * i);

      if (!self->kernel_start)
        self->kernel_start = section->addr;

      if (!self->kernel_end)
        self->kernel_end = section->addr;

      if (section->addr < self->kernel_start)
        self->kernel_start = section->addr;

      if (section->addr > self->kernel_end)
        self->kernel_end = section->addr;
    }
  }

  self->end_tag = tag;
  self->multiboot_end = (uintptr_t)(tag + tag->size);
}

void print_boot_info(boot_info_t *self)
{
  log("Boot Info:");

  log("\tCommand line = %s", self->command_line_tag->string);

  log("\tBoot loader name = %s", self->boot_loader_name_tag->string);

  log("\tModule at 0x%x-0x%x. Command line %s",
      self->module_tag->mod_start,
      self->module_tag->mod_end,
      self->module_tag->cmdline);

  log("\tmem_lower = %uKB, mem_upper = %uKB",
      self->basic_meminfo_tag->mem_lower,
      self->basic_meminfo_tag->mem_upper);

  log("\tBoot device 0x%x,%u,%u",
      self->boot_device_tag->biosdev,
      self->boot_device_tag->slice,
      self->boot_device_tag->part);

  if (self->elf_sections_tag)
  {
    log("\tELF Sections:");
    elf_section_t *section;
    for (uintptr_t i = 1; i < self->elf_sections_tag->num; i++)
    {
      section = (elf_section_t *)(self->elf_sections_tag->sections + self->elf_sections_tag->entsize * i);
      log("\t\taddr = 0x%x%x, offset = 0x%x, size = 0x%x, flags = 0x%x",
          section->addr,
          section->offset,
          section->size,
          section->flags);
    }
  }

  if (self->memory_map_tag)
  {
    int entry_count = self->memory_map_tag->size / self->memory_map_tag->entry_size;
    log("\tMemory Map: numEntries=0x%x", entry_count);

    multiboot_memory_map_t *mmap;
    for (int i = 0; i < entry_count; i++)
    {
      mmap = (multiboot_memory_map_t *)((uint8_t *)self->memory_map_tag->entries + (i * self->memory_map_tag->entry_size));
      log("\t\tbase_addr = 0x%x%x, length = 0x%x%x, type = 0x%x",
          (unsigned)(mmap->addr >> 32),
          (unsigned)(mmap->addr & 0xffffffff),
          (unsigned)(mmap->len >> 32),
          (unsigned)(mmap->len & 0xffffffff),
          (unsigned)mmap->type);
    }
  }

  if (self->framebuffer_tag)
  {
    log("\tFramebuffer: addr = 0x%x, type = 0x%x",
        self->framebuffer_tag->common.framebuffer_addr,
        self->framebuffer_tag->common.framebuffer_type);
    log("\t\twidth = 0x%x, height = 0x%x, pitch = 0x%x, colors = 0x%x",
        self->framebuffer_tag->common.framebuffer_width,
        self->framebuffer_tag->common.framebuffer_height,
        self->framebuffer_tag->common.framebuffer_pitch,
        self->framebuffer_tag->framebuffer_palette_num_colors);
  }

  log("\tKernel: start = 0x%x, end = 0x%x",
      self->kernel_start,
      self->kernel_end);

  log("\tMultiboot: start = 0x%x, end = 0x%x",
      self->multiboot_start,
      self->multiboot_end);
}