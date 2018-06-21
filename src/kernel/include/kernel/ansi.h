#pragma once

#include <stdint.h>

typedef struct ansi_state
{
  enum
  {
    ANSI_ESC,
    ANSI_BRACKET,
    ANSI_PARSE,
    ANSI_BGCOLOR,
    ANSI_BGCOLOR_BRIGHT,
    ANSI_FGCOLOR,
    ANSI_FGCOLOR_BRIGHT,
    ANSI_EQUALS,
    ANSI_ENDVAL,
  } state;
  uint16_t color;
  uint16_t next_color;
} ANSI_STATE;

typedef struct ansi_color_char
{
  uint16_t color;
  unsigned char ascii;
} ANSI_COLOR_CHAR;

struct ansi_state ansi_init(void);
struct ansi_color_char ansi_process(struct ansi_state *state, char x);