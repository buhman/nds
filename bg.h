#pragma once

#include <stdint.h>

#define static_assert _Static_assert

union bg_screen_block {
  uint8_t u8[0x800 / 1];
  uint16_t u16[0x800 / 2];
  uint32_t u32[0x800 / 4];
};
static_assert((sizeof (union bg_screen_block)) == 0x800);

struct bg_screen_offset {
  union bg_screen_block block[32];
};
static_assert((sizeof (struct bg_screen_offset)) == 0x10000);

struct bg_screen_data {
  struct bg_screen_offset offset[8];
};
static_assert((sizeof (struct bg_screen_data)) == 0x80000);

union bg_character {
  uint8_t u8[32 / 1];
  uint16_t u16[32 / 2];
  uint32_t u32[32 / 4];
};
static_assert((sizeof (union bg_character)) == 32);

union bg_character_block {
  union bg_character character[0x4000 / (sizeof (union bg_character))];
  union {
    uint8_t u8[0x4000 / 1];
    uint16_t u16[0x4000 / 2];
    uint32_t u32[0x4000 / 4];
  };
};
static_assert((sizeof (union bg_character_block)) == 0x4000);

struct bg_character_offset {
  union bg_character_block block[4]; // is actually 16
};

struct bg_character_data {
  struct bg_character_offset offset[8];
};
static_assert((sizeof (struct bg_character_data)) == 0x80000);

struct bg {
  union {
    struct bg_screen_data screen;
    struct bg_character_data character;
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
