#include "io_registers.h"
#include "bits.h"
#include "bg.h"
#include "palette.h"

#include "res/player.h"
#include "res/player.pal.h"

static inline uint16_t rgb555(const uint8_t * buf)
{
  uint8_t r = buf[0] >> 3;
  uint8_t g = buf[1] >> 3;
  uint8_t b = buf[2] >> 3;

  return (b << 10) | (g << 5) | (r << 0);
}

void main()
{
  io_registers.a.VRAMCNT = (1 << 31) | (1 << 24);
  io_registers.a.WVRAMCNT = 0;

  io_registers.a.DISPCNT = 0
    | DISPCNT__bg_screen_base_offset(0)
    | DISPCNT__bg_character_base_offset(0)
    | DISPCNT__display_mode__graphics_display
    | DISPCNT__bg0__enable
    | DISPCNT__display_selection_for_bg0__2d_graphics
    | DISPCNT__bg_mode__text0_text1_text2_text3
    ;

  io_registers.a.BG0CNT = 0
    | BG0CNT__screen_size__256x256
    | BG0CNT__screen_base_block(31)
    | BG0CNT__color_mode__16_color_mode
    | BG0CNT__character_base_block(0)
    | BG0CNT__priority(0)
    ;

  uint32_t pal_size = (uint32_t)&_binary_res_player_data_pal_size;
  const uint8_t * pal = (const uint8_t *)&_binary_res_player_data_pal_start;

  // palette ram
  for (int i = 0; i < 15; i++) {
    palette_ram.a.bg.palette[0].color[i] = rgb555(&pal[i * 3]);
  }

  const uint8_t * data = (const uint8_t *)&_binary_res_player_data_start;



  for (int y = 0; y < 48; y++) {
    uint8_t a = data[y * 8 + 0];
    uint8_t b = data[y * 8 + 1];
    uint8_t c = data[y * 8 + 2];
    uint8_t d = data[y * 8 + 3];
    uint8_t e = data[y * 8 + 4];
    uint8_t f = data[y * 8 + 5];
    uint8_t g = data[y * 8 + 6];
    uint8_t h = data[y * 8 + 7];

    bg_vram.a.character.offset[0].block[0].u32[y] = 0
      | (a << 28)
      | (b << 24)
      | (c << 20)
      | (d << 16)
      | (e << 12)
      | (f << 8)
      | (g << 4)
      | (h << 0);
  }

  for (int i = 0; i < 32 * 32; i++) {
    bg_vram.a.screen.offset[0].block[31].u16[i] = 30;
  }
  bg_vram.a.screen.offset[0].block[31].u16[32 * 0] = 3;
  bg_vram.a.screen.offset[0].block[31].u16[32 * 1] = 4;
  bg_vram.a.screen.offset[0].block[31].u16[32 * 2] = 5;
  bg_vram.a.screen.offset[0].block[31].u16[32 * 0 + 1] = 0;
  bg_vram.a.screen.offset[0].block[31].u16[32 * 1 + 1] = 1;
  bg_vram.a.screen.offset[0].block[31].u16[32 * 2 + 1] = 2;

  while (1);
}
