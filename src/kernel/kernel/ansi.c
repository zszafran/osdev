#include <kernel/ansi.h>
#include <kernel/vga.h>

#define ESC '\x1B'

struct ansi_state ansi_init(void)
{
  struct ansi_state ret = {
      .state = ANSI_ESC,
      .color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK),
      .next_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK),
  };
  return ret;
}

static inline enum vga_color convert_color(unsigned char color)
{
  const unsigned char lookup_table[8] = {
      VGA_COLOR_BLACK,
      VGA_COLOR_RED,
      VGA_COLOR_GREEN,
      VGA_COLOR_YELLOW,
      VGA_COLOR_BLUE,
      VGA_COLOR_MAGENTA,
      VGA_COLOR_CYAN,
      VGA_COLOR_LIGHT_GREY,
  };
  return lookup_table[(int)color];
}

static inline enum vga_color convert_bright_color(unsigned char color)
{
  const unsigned char lookup_table[8] = {
      VGA_COLOR_DARK_GREY,
      VGA_COLOR_LIGHT_RED,
      VGA_COLOR_LIGHT_GREEN,
      VGA_COLOR_LIGHT_YELLOW,
      VGA_COLOR_LIGHT_BLUE,
      VGA_COLOR_LIGHT_MAGENTA,
      VGA_COLOR_LIGHT_CYAN,
      VGA_COLOR_WHITE,
  };
  return lookup_table[(int)color];
}

struct ansi_color_char ansi_process(struct ansi_state *state, char x)
{
  ANSI_COLOR_CHAR rv = {
      .color = state->color,
      .ascii = '\0',
  };

  switch (state->state)
  {
  case ANSI_ESC:
    if (x == ESC)
      state->state = ANSI_BRACKET;
    else
    {
      rv.ascii = x;
    }
    break;
  case ANSI_BRACKET:
    if (x == '[')
      state->state = ANSI_PARSE;
    else
    {
      state->state = ANSI_ESC;
      rv.ascii = x;
    }
    break;
  case ANSI_PARSE:
    if (x == '3')
    {
      state->state = ANSI_FGCOLOR;
    }
    else if (x == '9')
    {
      state->state = ANSI_FGCOLOR_BRIGHT;
    }
    else if (x == '4')
    {
      state->state = ANSI_BGCOLOR;
    }
    else if (x == '0')
    {
      state->state = ANSI_ENDVAL;
      state->next_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    }
    else if (x == '1')
    {
      state->state = ANSI_ENDVAL;
      state->color |= (1 << 3);
    }
    else if (x == '=')
    {
      state->state = ANSI_EQUALS;
    }
    else
    {
      state->state = ANSI_ESC;
      state->next_color = state->color;
      rv.ascii = x;
    }
    break;
  case ANSI_BGCOLOR:
    if (x >= '0' && x <= '7')
    {
      state->state = ANSI_ENDVAL;
      state->next_color &= 0x1F;
      state->next_color |= convert_color(x - '0') << 4;
    }
    else
    {
      state->state = ANSI_ESC;
      state->next_color = state->color;
      rv.ascii = x;
    }
    break;
  case ANSI_FGCOLOR:
    if (x >= '0' && x <= '7')
    {
      state->state = ANSI_ENDVAL;
      state->next_color &= 0xF8;
      state->next_color |= convert_color(x - '0');
    }
    else
    {
      state->state = ANSI_ESC;
      state->next_color = state->color;
      rv.ascii = x;
    }
    break;
  case ANSI_FGCOLOR_BRIGHT:
    if (x >= '0' && x <= '7')
    {
      state->state = ANSI_ENDVAL;
      state->next_color &= 0xF8;
      state->next_color |= convert_bright_color(x - '0');
    }
    else
    {
      state->state = ANSI_ESC;
      state->next_color = state->color;
      rv.ascii = x;
    }
    break;
  case ANSI_EQUALS:
    if (x == '1')
    {
      state->state = ANSI_ENDVAL;
      state->next_color &= ~(1 << 3);
    }
    else
    {
      state->state = ANSI_ESC;
      state->next_color = state->color;
      rv.ascii = x;
    }
    break;
  case ANSI_ENDVAL:
    if (x == ';')
    {
      state->state = ANSI_PARSE;
    }
    else if (x == 'm')
    {
      // Finish and apply styles
      state->state = ANSI_ESC;
      state->color = state->next_color;
    }
    else
    {
      state->state = ANSI_ESC;
      state->next_color = state->color;
      rv.ascii = x;
    }
    break;
  default:
    break;
  }
  return rv;
}