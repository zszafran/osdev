#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/ansi.h>
#include <kernel/tty.h>
#include <kernel/vga.h>

static size_t terminal_width;
static size_t terminal_height;
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t *terminal_buffer;
static struct ansi_state terminal_color_state;

void terminal_initialize(unsigned long long framebuffer_addr,
                         unsigned int width,
                         unsigned int height)
{
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal_buffer = (uint16_t *)framebuffer_addr;
  terminal_width = width;
  terminal_height = height;
  terminal_color_state = ansi_init();
  terminal_clear();
}

void terminal_clear()
{
  for (size_t y = 0; y < terminal_height; y++)
  {
    for (size_t x = 0; x < terminal_width; x++)
    {
      const size_t index = y * terminal_width + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}

void terminal_shift_up()
{
  for (size_t y = 0; y < terminal_height - 1; y++)
  {
    for (size_t x = 0; x < terminal_width; x++)
    {
      const size_t target = y * terminal_width + x;
      const size_t source = (y + 1) * terminal_width + x;
      terminal_buffer[target] = terminal_buffer[source];
    }
  }
  for (size_t x = 0; x < terminal_width; x++)
  {
    const size_t index = (terminal_height - 1) * terminal_width + x;
    terminal_buffer[index] = vga_entry(' ', terminal_color);
  }
}

void terminal_setcolor(uint8_t color)
{
  terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y)
{
  const size_t index = y * terminal_width + x;
  terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
  unsigned char uc = c;

  if (uc == '\n')
  {
    terminal_column = 0;
    terminal_row++;
    return;
  }

  if (uc == '\t')
  {
    terminal_column += 2;
    return;
  }

  if (terminal_row == terminal_height)
  {
    terminal_shift_up();
    terminal_row = terminal_height - 1;
  }

  terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);

  if (++terminal_column == terminal_width)
  {
    terminal_column = 0;
    ++terminal_row;
  }
}

void terminal_write(const char *data, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    struct ansi_color_char color_char = ansi_process(&terminal_color_state, data[i]);
    if (color_char.ascii != '\0')
    {
      terminal_setcolor(color_char.color);
      terminal_putchar(color_char.ascii);
    }
  }
}

void terminal_writestring(const char *data)
{
  terminal_write(data, strlen(data));
}
