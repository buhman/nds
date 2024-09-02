#pragma once

#include <stdint.h>

#define static_assert _Static_assert

union obj_character {
  uint8_t u8[32 / 1];
  uint16_t u16[32 / 2];
  uint32_t u32[32 / 4];
};
static_assert((sizeof (union obj_character)) == 32);

union obj {
  union obj_character character[1024];
  union {
    uint8_t u8[0x8000 / 1];
    uint16_t u16[0x8000 / 2];
    uint32_t u32[0x8000 / 4];
  };
};
static_assert((sizeof (union obj)) == 0x8000);

struct obj_vram {
  union obj a;
  uint8_t _pad[0x200000 - (sizeof (union obj))];
  union obj b;
};
static_assert((offsetof (struct obj_vram, a)) == 0);
static_assert((offsetof (struct obj_vram, b)) == 0x200000);

extern struct obj_vram obj_vram __asm("obj_vram");
