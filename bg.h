#pragma once

#include <stdint.h>

#define static_assert _Static_assert

union screen_block {
  uint8_t u8[0x800 / 1];
  uint16_t u16[0x800 / 2];
  uint32_t u32[0x800 / 4];
};
static_assert((sizeof (union screen_block)) == 0x800);

struct screen_offset {
  union screen_block block[32];
};
static_assert((sizeof (struct screen_offset)) == 0x10000);

struct screen_data {
  struct screen_offset offset[8];
};
static_assert((sizeof (struct screen_data)) == 0x80000);

union character_block {
  uint16_t u8[0x4000 / 2];
  uint16_t u16[0x4000 / 2];
  uint32_t u32[0x4000 / 4];
};
static_assert((sizeof (union character_block)) == 0x4000);

struct character_offset {
  union character_block block[4]; // is actually 16
};

struct character_data {
  struct character_offset offset[8];
};
static_assert((sizeof (struct character_data)) == 0x80000);

struct bg {
  union {
    struct screen_data screen;
    struct character_data character;
  };
};
static_assert((sizeof (struct bg)) == 0x80000);

struct bg_vram {
  struct bg a;
  uint8_t _pad[0x200000 - (sizeof (struct bg))];
  struct bg b;
};
static_assert((offsetof (struct bg_vram, a)) == 0);
static_assert((offsetof (struct bg_vram, b)) == 0x200000);

extern struct bg_vram bg_vram __asm("bg_vram");
