#pragma once

#include <stdint.h>

#define static_assert _Static_assert

struct color16 {
  uint16_t color[16];
};
static_assert((sizeof (struct color16)) == 0x20);

union palette {
  struct color16 palette[16];
  uint16_t color[256];
};
static_assert((sizeof (union palette)) == 0x200);

struct palette_bg_obj {
  union palette bg;
  union palette obj;
};
static_assert((sizeof (struct palette_bg_obj)) == 0x400);

struct palette_a_b {
  struct palette_bg_obj a;
  struct palette_bg_obj b;
};
static_assert((sizeof (struct palette_a_b)) == 0x800);

extern struct palette_a_b palette_ram __asm("palette_ram");
