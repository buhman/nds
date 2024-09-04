#include "io_registers.h"
#include "bits.h"

#include "res/hotaru_futaba.data.h"
#include "res/hotaru_futaba.data.pal.h"

static inline uint16_t rgb565(const uint8_t * buf)
{
  uint8_t r = buf[0] >> 3;
  uint8_t g = buf[1] >> 3;
  uint8_t g_l = (buf[1] >> 2) & 1;
  uint8_t b = buf[2] >> 3;

  return (g_l << 15) | (b << 10) | (g << 5) | (r << 0);
}

void main()
{
  // power control
  io_registers.a.POWCNT = 0
    | POWCNT__lcd_output_destination__a_to_upper__b_to_lower
    | POWCNT__geometry_engine__enable
    | POWCNT__rendering_engine__enable
    | POWCNT__lcd__enable;

  // enable bg0 and 3d graphics
  io_registers.a.DISPCNT = 0
    | DISPCNT__display_mode__graphics_display
    | DISPCNT__bg0__enable
    | DISPCNT__display_selection_for_bg0__3d_graphics
    ;

  // disable all 3d effects, enable texture mapping
  io_registers.a.DISP3DCNT = 0
    | DISP3DCNT__clear_image__disable
    | DISP3DCNT__fog_master__disable
    | DISP3DCNT__edge_marking__disable
    | DISP3DCNT__anti_aliasing__disable
    | DISP3DCNT__alpha_blending__disable
    | DISP3DCNT__alpha_test__disable
    | DISP3DCNT__texture_mapping__enable;

  // memory bank allocation
  // use VRAM-A for texture pixel data
  // use VRAM-E for texture palette data

  // temporarily map VRAM-A (128KB) to the arm9 address space:
  // 0x06800000 - 0x0681FFFF
  io_registers.a.VRAMCNT = 0
    | VRAMCNT__vram_a__enable
    | VRAMCNT__vram_a__mst(0b00); // arm9

  // temporarily map VRAM-F (16KB) to the arm9 address space:
  // 0x06890000 - 0x06893FFF
  io_registers.a.WVRAMCNT = 0
    | WVRAMCNT__vram_f__enable
    | WVRAMCNT__vram_f__mst(0b000); // arm9

  // at this point, VRAM-A/VRAM-E are not accessible by the 3d engine.

  // copy palette data
  const uint8_t * pal = (const uint8_t *)&_binary_hotaru_futaba_data_pal_start;
  volatile uint16_t * vram_f = (volatile uint16_t *)(0x06890000);
  for (int i = 0; i < 16; i++) {
    // as exported by GIMP, the palette data is three bytes per pixel, packed
    // RGB24
    vram_f[i] = rgb565(&pal[i * 3]);
  }

  // copy pixel data
  const uint8_t * pixels = (const uint8_t *)&_binary_hotaru_futaba_data_start;
  volatile uint16_t * vram_a = (volatile uint16_t *)(0x06800000);

  // notice the += 2 increment
  for (int i = 0; i < 96 * 64; i += 2) {
    // as exported by GIMP, the pixel data is two bytes per pixel.
    // [0]: color index (0-15)
    // [1]: alpha (0 or 255)

    // generate a3i5 pixel data:
    // | 15 14 13 | 12 10 09 08 | 07 06 05 | 04 03 02 01 00 |
    // | t1 alpha | t1 index    | t0 alpha | t0 index       |

    // process two pixels per loop iteration
    uint8_t t0_index = pixels[(i + 0) * 2 + 0];
    uint8_t t0_alpha = pixels[(i + 0) * 2 + 1];

    uint8_t t1_index = pixels[(i + 1) * 2 + 0];
    uint8_t t1_alpha = pixels[(i + 1) * 2 + 1];

    // scale alpha from 8-bit to 3-bit
    t0_alpha >>= 5;
    t1_alpha >>= 5;

    // mask index to 4-bit (though the data should already be 16-color, just in case)
    t0_index &= 0xf;
    t1_index &= 0xf;

    // the data is now one byte per a3i5 texel, two a3i5 texels per uint16_t
    uint16_t a3i5_texel = (t1_alpha << 13) | (t1_index << 8) | (t0_alpha << 5) | (t0_index << 0);
    vram_a[i / 2] = a3i5_texel;
  }

  // arm9 no longer needs read/write access to texture data, remap vram to the 3d engine

  // map VRAM-A (128KB) to the 3d-engine "texture image slot 0":
  // 0x00000 - 0x1ffff (3d engine texture image address space)
  io_registers.a.VRAMCNT = 0
    | VRAMCNT__vram_a__enable
    | VRAMCNT__vram_a__ofs(0)     // slot 0
    | VRAMCNT__vram_a__mst(0b11); // texture image

  // map VRAM-F (16KB) to the 3d-engine "texture palette slot 0":
  // 0x0000 - 0x3fff (3d engine texture palette address space)
  io_registers.a.WVRAMCNT = 0
    | WVRAMCNT__vram_f__enable
    | WVRAMCNT__vram_f__ofs(0)      // slot 0
    | WVRAMCNT__vram_f__mst(0b011); // texture palette

  // set the texture palette base address
  io_registers.a.TEXPLTT_BASE = TEXPLTT_BASE__base_address(0);

  io_registers.a.TEXIMAGE_PARAM = 0
    | TEXIMAGE_PARAM__texture_coordinate_transformation_mode__texcoord_source
    | TEXIMAGE_PARAM__texture_format__a3i5_translucent
    | TEXIMAGE_PARAM__t_size__128_texels // actually 96 pixels
    | TEXIMAGE_PARAM__s_size__64_texels
    | TEXIMAGE_PARAM__texture_starting_address(0);

  // the following polygons are fully opaque and are not
  // backface-culled
  // use
  io_registers.a.POLYGON_ATTR = 0
    | POLYGON_ATTR__alpha_value(31)
    | POLYGON_ATTR__render_front_surface__enable
    | POLYGON_ATTR__render_back_surface__enable;

  // clear matrix stack status
  io_registers.a.GXSTAT |= GXSTAT__matrix_stack_status__overflow_or_underflow;

  // load identity matrices
  io_registers.a.MTX_MODE = MTX_MODE__matrix_mode__projection;
  io_registers.a.MTX_IDENTITY = 0;
  // scale the x-axis by the ratio of the display height by the display width.
  io_registers.a.MTX_SCALE = (192 << 12) / 256;
  io_registers.a.MTX_SCALE = 1 << 12;
  io_registers.a.MTX_SCALE = 1 << 12;

  io_registers.a.MTX_MODE = MTX_MODE__matrix_mode__position_and_vector;
  io_registers.a.MTX_IDENTITY = 0;

  io_registers.a.MTX_MODE = MTX_MODE__matrix_mode__position;
  io_registers.a.MTX_IDENTITY = 0;
  // scale the x-axis by the ratio of the hotaru sprite dimensions
  io_registers.a.MTX_SCALE = (64 << 12) / 96;
  io_registers.a.MTX_SCALE = 1 << 12;
  io_registers.a.MTX_SCALE = 1 << 12;

  io_registers.a.MTX_MODE = MTX_MODE__matrix_mode__texture;
  io_registers.a.MTX_IDENTITY = 0;

  // set the 3d clear color to a dark red
  io_registers.a.CLEAR_COLOR = 0
    | CLEAR_COLOR__clear_polygon_id(31)
    | CLEAR_COLOR__alpha_value(31)
    | CLEAR_COLOR__blue(1)
    | CLEAR_COLOR__green(1)
    | CLEAR_COLOR__red(10);

  // set the depth buffer clear value to the maximum value
  io_registers.a.CLEAR_DEPTH = CLEAR_DEPTH__value(0x7fff);

  // the 3d viewport is the entire display area
  io_registers.a.VIEWPORT = 0
    | VIEWPORT__y2(191)
    | VIEWPORT__x2(255)
    | VIEWPORT__y1(0)
    | VIEWPORT__x1(0);

  // VTX_10 uses signed 4.6 floating point (10 bit)
  // | 9 | 8 7 6 | 5 4 3 2 1 0 |
  // | s |  int  | decimal     |
  int vtx_10_fixed_point = 64; // == 2⁶

  // TEXCOORD uses signed 12.4 floating point (16 bit)
  int texcoord_fixed_point = 16; // == 2⁴

  // quadrilateral; top-left corner is top-left of screen
  /*
      A--D
      |  |
      |  |
      B--C

      abcd
  */
  int ax = -1.0 * vtx_10_fixed_point;
  int ay =  1.0 * vtx_10_fixed_point;
  int as =  0.0 * texcoord_fixed_point;
  int at =  0.0 * texcoord_fixed_point;

  int bx = -1.0 * vtx_10_fixed_point;
  int by = -1.0 * vtx_10_fixed_point;
  int bs =  0.0 * texcoord_fixed_point;
  int bt = 95.0 * texcoord_fixed_point;

  int cx =  1.0 * vtx_10_fixed_point;
  int cy = -1.0 * vtx_10_fixed_point;
  int cs = 63.0 * texcoord_fixed_point;
  int ct = 95.0 * texcoord_fixed_point;

  int dx =  1.0 * vtx_10_fixed_point;
  int dy =  1.0 * vtx_10_fixed_point;
  int ds = 63.0 * texcoord_fixed_point;
  int dt =  0.0 * texcoord_fixed_point;

  int z  =  1.0 * vtx_10_fixed_point;

  while (1) {
    io_registers.a.COLOR = 0
      | COLOR__blue(31)
      | COLOR__green(31)
      | COLOR__red(31);

    // first quadrilateral: ABCD
    io_registers.a.BEGIN_VTXS = BEGIN_VTXS__type__quadrilateral;

    io_registers.a.TEXCOORD = 0
      | TEXCOORD__t_coordinate(at)
      | TEXCOORD__s_coordinate(as);
    io_registers.a.VTX_10 = 0
      | VTX_10__z_coordinate(z)
      | VTX_10__y_coordinate(ay)
      | VTX_10__x_coordinate(ax);

    io_registers.a.TEXCOORD = 0
      | TEXCOORD__t_coordinate(bt)
      | TEXCOORD__s_coordinate(bs);
    io_registers.a.VTX_10 = 0
      | VTX_10__z_coordinate(z)
      | VTX_10__y_coordinate(by)
      | VTX_10__x_coordinate(bx);

    io_registers.a.TEXCOORD = 0
      | TEXCOORD__t_coordinate(ct)
      | TEXCOORD__s_coordinate(cs);
    io_registers.a.VTX_10 = 0
      | VTX_10__z_coordinate(z)
      | VTX_10__y_coordinate(cy)
      | VTX_10__x_coordinate(cx);

    io_registers.a.TEXCOORD = 0
      | TEXCOORD__t_coordinate(dt)
      | TEXCOORD__s_coordinate(ds);
    io_registers.a.VTX_10 = 0
      | VTX_10__z_coordinate(z)
      | VTX_10__y_coordinate(dy)
      | VTX_10__x_coordinate(dx);

    // end of the ABCD quadrilateral
    io_registers.a.END_VTXS = 0;

    // wait for the geometry engine
    while (io_registers.a.GXSTAT & GXSTAT__geometry_engine_busy);

    while (io_registers.a.VCOUNT != 262);
    while (io_registers.a.VCOUNT != 0);

    // swap buffers
    io_registers.a.SWAP_BUFFERS = 0;
  }
}
