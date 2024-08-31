#include "io_registers.h"
#include "bits.h"
#include "bg.h"
#include "palette.h"
#include "obj.h"
#include "oam.h"

#include "res/player.h"
#include "res/player.pal.h"
#include "res/bowser.h"
#include "res/bowser.pal.h"

static inline uint16_t rgb565(const uint8_t * buf)
{
  uint8_t r = buf[0] >> 3;
  uint8_t g = buf[1] >> 3;
  uint8_t g_l = (buf[1] >> 2) & 1;
  uint8_t b = buf[2] >> 3;

  return (g_l << 15) | (b << 10) | (g << 5) | (r << 0);
}

struct sign_v {
  char sign;
  uint8_t v;
};

struct sign_v cos_table[360] = {
  {0, 255},
  {0, 254},
  {0, 254},
  {0, 254},
  {0, 254},
  {0, 254},
  {0, 253},
  {0, 253},
  {0, 252},
  {0, 251},
  {0, 251},
  {0, 250},
  {0, 249},
  {0, 248},
  {0, 247},
  {0, 246},
  {0, 245},
  {0, 243},
  {0, 242},
  {0, 241},
  {0, 239},
  {0, 238},
  {0, 236},
  {0, 234},
  {0, 232},
  {0, 231},
  {0, 229},
  {0, 227},
  {0, 225},
  {0, 223},
  {0, 220},
  {0, 218},
  {0, 216},
  {0, 213},
  {0, 211},
  {0, 208},
  {0, 206},
  {0, 203},
  {0, 200},
  {0, 198},
  {0, 195},
  {0, 192},
  {0, 189},
  {0, 186},
  {0, 183},
  {0, 180},
  {0, 177},
  {0, 173},
  {0, 170},
  {0, 167},
  {0, 163},
  {0, 160},
  {0, 156},
  {0, 153},
  {0, 149},
  {0, 146},
  {0, 142},
  {0, 138},
  {0, 135},
  {0, 131},
  {0, 127},
  {0, 123},
  {0, 119},
  {0, 115},
  {0, 111},
  {0, 107},
  {0, 103},
  {0, 99},
  {0, 95},
  {0, 91},
  {0, 87},
  {0, 83},
  {0, 78},
  {0, 74},
  {0, 70},
  {0, 65},
  {0, 61},
  {0, 57},
  {0, 53},
  {0, 48},
  {0, 44},
  {0, 39},
  {0, 35},
  {0, 31},
  {0, 26},
  {0, 22},
  {0, 17},
  {0, 13},
  {0, 8},
  {0, 4},
  {0, 0},
  {1, 4},
  {1, 8},
  {1, 13},
  {1, 17},
  {1, 22},
  {1, 26},
  {1, 31},
  {1, 35},
  {1, 39},
  {1, 44},
  {1, 48},
  {1, 53},
  {1, 57},
  {1, 61},
  {1, 65},
  {1, 70},
  {1, 74},
  {1, 78},
  {1, 83},
  {1, 87},
  {1, 91},
  {1, 95},
  {1, 99},
  {1, 103},
  {1, 107},
  {1, 111},
  {1, 115},
  {1, 119},
  {1, 123},
  {1, 127},
  {1, 131},
  {1, 135},
  {1, 138},
  {1, 142},
  {1, 146},
  {1, 149},
  {1, 153},
  {1, 156},
  {1, 160},
  {1, 163},
  {1, 167},
  {1, 170},
  {1, 173},
  {1, 177},
  {1, 180},
  {1, 183},
  {1, 186},
  {1, 189},
  {1, 192},
  {1, 195},
  {1, 198},
  {1, 200},
  {1, 203},
  {1, 206},
  {1, 208},
  {1, 211},
  {1, 213},
  {1, 216},
  {1, 218},
  {1, 220},
  {1, 223},
  {1, 225},
  {1, 227},
  {1, 229},
  {1, 231},
  {1, 232},
  {1, 234},
  {1, 236},
  {1, 238},
  {1, 239},
  {1, 241},
  {1, 242},
  {1, 243},
  {1, 245},
  {1, 246},
  {1, 247},
  {1, 248},
  {1, 249},
  {1, 250},
  {1, 251},
  {1, 251},
  {1, 252},
  {1, 253},
  {1, 253},
  {1, 254},
  {1, 254},
  {1, 254},
  {1, 254},
  {1, 254},
  {1, 255},
  {1, 254},
  {1, 254},
  {1, 254},
  {1, 254},
  {1, 254},
  {1, 253},
  {1, 253},
  {1, 252},
  {1, 251},
  {1, 251},
  {1, 250},
  {1, 249},
  {1, 248},
  {1, 247},
  {1, 246},
  {1, 245},
  {1, 243},
  {1, 242},
  {1, 241},
  {1, 239},
  {1, 238},
  {1, 236},
  {1, 234},
  {1, 232},
  {1, 231},
  {1, 229},
  {1, 227},
  {1, 225},
  {1, 223},
  {1, 220},
  {1, 218},
  {1, 216},
  {1, 213},
  {1, 211},
  {1, 208},
  {1, 206},
  {1, 203},
  {1, 200},
  {1, 198},
  {1, 195},
  {1, 192},
  {1, 189},
  {1, 186},
  {1, 183},
  {1, 180},
  {1, 177},
  {1, 173},
  {1, 170},
  {1, 167},
  {1, 163},
  {1, 160},
  {1, 156},
  {1, 153},
  {1, 149},
  {1, 146},
  {1, 142},
  {1, 138},
  {1, 135},
  {1, 131},
  {1, 127},
  {1, 123},
  {1, 119},
  {1, 115},
  {1, 111},
  {1, 107},
  {1, 103},
  {1, 99},
  {1, 95},
  {1, 91},
  {1, 87},
  {1, 83},
  {1, 78},
  {1, 74},
  {1, 70},
  {1, 65},
  {1, 61},
  {1, 57},
  {1, 53},
  {1, 48},
  {1, 44},
  {1, 39},
  {1, 35},
  {1, 31},
  {1, 26},
  {1, 22},
  {1, 17},
  {1, 13},
  {1, 8},
  {1, 4},
  {1, 0},
  {0, 4},
  {0, 8},
  {0, 13},
  {0, 17},
  {0, 22},
  {0, 26},
  {0, 31},
  {0, 35},
  {0, 39},
  {0, 44},
  {0, 48},
  {0, 53},
  {0, 57},
  {0, 61},
  {0, 65},
  {0, 70},
  {0, 74},
  {0, 78},
  {0, 83},
  {0, 87},
  {0, 91},
  {0, 95},
  {0, 99},
  {0, 103},
  {0, 107},
  {0, 111},
  {0, 115},
  {0, 119},
  {0, 123},
  {0, 127},
  {0, 131},
  {0, 135},
  {0, 138},
  {0, 142},
  {0, 146},
  {0, 149},
  {0, 153},
  {0, 156},
  {0, 160},
  {0, 163},
  {0, 167},
  {0, 170},
  {0, 173},
  {0, 177},
  {0, 180},
  {0, 183},
  {0, 186},
  {0, 189},
  {0, 192},
  {0, 195},
  {0, 198},
  {0, 200},
  {0, 203},
  {0, 206},
  {0, 208},
  {0, 211},
  {0, 213},
  {0, 216},
  {0, 218},
  {0, 220},
  {0, 223},
  {0, 225},
  {0, 227},
  {0, 229},
  {0, 231},
  {0, 232},
  {0, 234},
  {0, 236},
  {0, 238},
  {0, 239},
  {0, 241},
  {0, 242},
  {0, 243},
  {0, 245},
  {0, 246},
  {0, 247},
  {0, 248},
  {0, 249},
  {0, 250},
  {0, 251},
  {0, 251},
  {0, 252},
  {0, 253},
  {0, 253},
  {0, 254},
  {0, 254},
  {0, 254},
  {0, 254},
  {0, 254}
};

void main()
{
  // 2d graphics engine A BG
  io_registers.a.VRAMCNT = (1 << 31) | (1 << 24);

  io_registers.a.WVRAMCNT = 0;

  // 2d graphics engine B OBJ
  io_registers.a.VRAM_HI_CNT = (1 << 15) | (0b10 << 8);

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

  io_registers.b.DISPCNT = 0
    | DISPCNT__display_mode__graphics_display
    | DISPCNT__obj__enable
    | DISPCNT__character_obj_mapping_mode__1d_mapping
    ;

  uint32_t pal_size = (uint32_t)&_binary_res_player_data_pal_size;
  const uint8_t * pal = (const uint8_t *)&_binary_res_player_data_pal_start;

  // palette ram
  for (int i = 0; i < 15; i++) {
    palette_ram.a.bg.palette[0].color[i] = rgb565(&pal[i * 3]);
  }

  uint32_t b_pal_size = (uint32_t)&_binary_res_bowser_data_pal_size;
  const uint8_t * b_pal = (const uint8_t *)&_binary_res_bowser_data_pal_start;

  // bowser palette ram
  for (int i = 0; i < 16; i++) {
    palette_ram.b.obj.palette[0].color[i] = rgb565(&b_pal[i * 3]);
  }

  const uint8_t * data = (const uint8_t *)&_binary_res_player_data_start;

  for (int y = 0; y < 48; y++) {
    uint8_t a = data[y * 8 + 7];
    uint8_t b = data[y * 8 + 6];
    uint8_t c = data[y * 8 + 5];
    uint8_t d = data[y * 8 + 4];
    uint8_t e = data[y * 8 + 3];
    uint8_t f = data[y * 8 + 2];
    uint8_t g = data[y * 8 + 1];
    uint8_t h = data[y * 8 + 0];

    bg_vram.a.character.offset[0].block[0].character[0].u32[y] = 0
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
  bg_vram.a.screen.offset[0].block[31].u16[32 * 0] = 0;
  bg_vram.a.screen.offset[0].block[31].u16[32 * 1] = 1;
  bg_vram.a.screen.offset[0].block[31].u16[32 * 2] = 2;
  bg_vram.a.screen.offset[0].block[31].u16[32 * 0 + 1] = 3;
  bg_vram.a.screen.offset[0].block[31].u16[32 * 1 + 1] = 4;
  bg_vram.a.screen.offset[0].block[31].u16[32 * 2 + 1] = 5;

  const uint8_t * b_data = (const uint8_t *)&_binary_res_bowser_data_start;

  for (int c_y = 0; c_y < 8; c_y++) {
    for (int c_x = 0; c_x < 8; c_x++) {
      for (int y = 0; y < 8; y++) {
	int abs_y = c_y * 8 + y;
	int abs_x = c_x * 8;
	int origin = abs_y * 64 + abs_x;

	uint8_t a = b_data[origin + 7];
	uint8_t b = b_data[origin + 6];
	uint8_t c = b_data[origin + 5];
	uint8_t d = b_data[origin + 4];
	uint8_t e = b_data[origin + 3];
	uint8_t f = b_data[origin + 2];
	uint8_t g = b_data[origin + 1];
	uint8_t h = b_data[origin + 0];

	obj_vram.b.character[c_y * 8 + c_x].u32[y] = 0
	  | (a << 28)
	  | (b << 24)
	  | (c << 20)
	  | (d << 16)
	  | (e << 12)
	  | (f << 8)
	  | (g << 4)
	  | (h << 0);
      }
    }
  }

  oam.b.obj[0].attr[0] = 0
    | OBJ_ATTRIBUTE_0__obj_shape__square
    | OBJ_ATTRIBUTE_0__color_mode__16_color_mode
    | OBJ_ATTRIBUTE_0__obj_mode__normal
    | OBJ_ATTRIBUTE_0__double_size__disable
    | OBJ_ATTRIBUTE_0__affine_transformation__enable
    //| OBJ_ATTRIBUTE_0__affine_transformation__disable
    | OBJ_ATTRIBUTE_0__y_coordinate(15)
    ;

  oam.b.obj[0].attr[1] = 0
    | OBJ_ATTRIBUTE_1__obj_size(0b11) // 64x64
    | OBJ_ATTRIBUTE_1__x_coordinate(20)
    | OBJ_ATTRIBUTE_1__affine_transformation_parameter(0)
    ;

  oam.b.obj[0].attr[2] = 0
    | OBJ_ATTRIBUTE_2__display_priority(0)
    | OBJ_ATTRIBUTE_2__character_name(0)
    ;

  /*
    dx (reference distance in x-direction for same line) =
    (1/α)cosθ
    dy (reference distance in y-direction for same line) =
    - (1/β)sinθ
    dmx (reference distance in x-direction for next line) =
    (1/α)sinθ
    dmy (reference distance in y-direction for next line) =
    (1/β)cosθ
  */

  int theta = 0;
  while (1) {
    struct sign_v cos = cos_table[theta];
    int sin_theta = theta + 90;
    if (sin_theta >= 360) sin_theta -= 360;
    struct sign_v sin = cos_table[sin_theta];

    // dx
    oam.b.param[0].pa = cos.sign ? cos.v : -cos.v;

    // dmx
    oam.b.param[0].pb = sin.sign ? sin.v : -sin.v;

    // dy
    oam.b.param[0].pc = sin.sign ? -sin.v : sin.v;

    // dmy
    oam.b.param[0].pd = cos.sign ? cos.v : -cos.v;

    theta += 1;
    if (theta >= 360) {
      theta = 0;
    }

    while (io_registers.a.VCOUNT != 262);
    while (io_registers.a.VCOUNT != 0);
  }
}
