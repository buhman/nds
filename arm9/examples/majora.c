#include "io_registers.h"
#include "bits.h"

#include "math/math.h"

#include "texture/060067E0.data.h"
#include "texture/060067E0.data.pal.h"
#include "texture/060077E0.data.h"
#include "texture/060077E0.data.pal.h"
#include "texture/060079E0.data.h"
#include "texture/060079E0.data.pal.h"
#include "texture/06007BE0.data.h"
#include "texture/06007BE0.data.pal.h"
#include "texture/06007DE0.data.h"
#include "texture/06007DE0.data.pal.h"
#include "texture/06007FE0.data.h"
#include "texture/06007FE0.data.pal.h"

#include "res/majora.h"
#include "model/majora.h"

struct object * object[6] = {
  &majora_1,
  &majora_3,
  &majora_4,
  &majora_5,
  &majora_6,
  &majora_7,
};

void copy_palettes()
{
  volatile uint16_t * vram_f = (volatile uint16_t *)(0x06890000);

  int palettes = (sizeof (material)) / (sizeof (material[0]));
  for (int i = 0; i < palettes; i++) {
    int colors = material[i].palette.size / 2;
    uint16_t * pal = (uint16_t *)material[i].palette.start;
    int offset = material[i].palette.vram_offset;

    for (int c = 0; c < colors; c++) {
      vram_f[c + offset / 2] = pal[c];
    }
  }
}

int pixel_dimension_from_pixels(int pixels)
{
  switch (pixels) {
  default:
  case 64:      return 8;
  case 256:     return 16;
  case 1024:    return 32;
  case 4096:    return 64;
  case 16384:   return 128;
  case 65536:   return 256;
  case 262144:  return 512;
  case 1048576: return 1024;
  }
}

uint32_t teximage_param__t_size(int height)
{
  switch (height) {
  default:
  case 8:       return TEXIMAGE_PARAM__t_size__8_texels;
  case 16:      return TEXIMAGE_PARAM__t_size__16_texels;
  case 32:      return TEXIMAGE_PARAM__t_size__32_texels;
  case 64:      return TEXIMAGE_PARAM__t_size__64_texels;
  case 128:     return TEXIMAGE_PARAM__t_size__128_texels;
  case 256:     return TEXIMAGE_PARAM__t_size__256_texels;
  case 512:     return TEXIMAGE_PARAM__t_size__512_texels;
  case 1024:    return TEXIMAGE_PARAM__t_size__1024_texels;
  }
}

uint32_t teximage_param__s_size(int width)
{
  switch (width) {
  default:
  case 8:       return TEXIMAGE_PARAM__s_size__8_texels;
  case 16:      return TEXIMAGE_PARAM__s_size__16_texels;
  case 32:      return TEXIMAGE_PARAM__s_size__32_texels;
  case 64:      return TEXIMAGE_PARAM__s_size__64_texels;
  case 128:     return TEXIMAGE_PARAM__s_size__128_texels;
  case 256:     return TEXIMAGE_PARAM__s_size__256_texels;
  case 512:     return TEXIMAGE_PARAM__s_size__512_texels;
  case 1024:    return TEXIMAGE_PARAM__s_size__1024_texels;
  }
}

uint32_t teximage_param__color_palette(int palette_size)
{
  switch (palette_size) {
  default:
  case 4:   return TEXIMAGE_PARAM__texture_format__4_color_palette;
  case 16:  return TEXIMAGE_PARAM__texture_format__16_color_palette;
  case 256: return TEXIMAGE_PARAM__texture_format__256_color_palette;
  }
}

void copy_pixels()
{
  volatile uint16_t * vram_a = (volatile uint16_t *)(0x06800000);

  int pixels = (sizeof (material)) / (sizeof (material[0]));
  *((volatile uint32_t *)0x4440000) = pixels;
  for (int i = 0; i < pixels; i++) {
    int size = material[i].pixel.size;
    uint16_t * pixel = (uint16_t *)material[i].pixel.start;
    int offset = material[i].pixel.vram_offset;

    *((volatile uint32_t *)0x4440000) = size;

    for (int t = 0; t < size / 2; t++) {
      vram_a[t + offset / 2] = pixel[t];
    }

    break;
  }
}

int u_to_s(int n, int dimension)
{
  return (n * dimension) >> 10;
}

int v_to_t(int n, int dimension)
{
  return ((((1 << 15) - n) * dimension) >> 10);
}

void copy_texture_data()
{
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

  copy_palettes();
  copy_pixels();

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

  // disable all 3d effects
  io_registers.a.DISP3DCNT = 0
    | DISP3DCNT__clear_image__disable
    | DISP3DCNT__fog_master__disable
    | DISP3DCNT__edge_marking__disable
    | DISP3DCNT__anti_aliasing__disable
    | DISP3DCNT__alpha_blending__disable
    | DISP3DCNT__alpha_test__disable
    | DISP3DCNT__texture_mapping__enable;

  copy_texture_data();

  // clear matrix stack status
  io_registers.a.GXSTAT |= GXSTAT__matrix_stack_status__overflow_or_underflow;

  // load identity matrices
  io_registers.a.MTX_MODE = MTX_MODE__matrix_mode__projection;
  io_registers.a.MTX_IDENTITY = 0;

  /*
  io_registers.a.MTX_SCALE = ((192 << 12) / (256)) / 2;
  io_registers.a.MTX_SCALE = 0.5 * 4096;
  io_registers.a.MTX_SCALE = 0.5 * 4096;
  */

  // load a symmetric perspective matrix, with aspect ratio correction
  io_registers.a.MTX_LOAD_4X4 = (192 << 12) / 256;
  io_registers.a.MTX_LOAD_4X4 = 0;
  io_registers.a.MTX_LOAD_4X4 = 0;
  io_registers.a.MTX_LOAD_4X4 = 0;

  io_registers.a.MTX_LOAD_4X4 = 0;
  io_registers.a.MTX_LOAD_4X4 = 1 << 12;
  io_registers.a.MTX_LOAD_4X4 = 0;
  io_registers.a.MTX_LOAD_4X4 = 0;

  io_registers.a.MTX_LOAD_4X4 = 0;
  io_registers.a.MTX_LOAD_4X4 = 0;
  io_registers.a.MTX_LOAD_4X4 = 0;
  io_registers.a.MTX_LOAD_4X4 = -(1 << 12);

  io_registers.a.MTX_LOAD_4X4 = 0;
  io_registers.a.MTX_LOAD_4X4 = 0;
  io_registers.a.MTX_LOAD_4X4 = -(1 << 12);
  io_registers.a.MTX_LOAD_4X4 = 0;

  // translate the viewpoint
  io_registers.a.MTX_TRANS = 0;
  io_registers.a.MTX_TRANS = 0;
  io_registers.a.MTX_TRANS = (int)(-2.0 * (float)(1 << 12));

  io_registers.a.MTX_MODE = MTX_MODE__matrix_mode__position;
  io_registers.a.MTX_IDENTITY = 0;

  io_registers.a.MTX_MODE = MTX_MODE__matrix_mode__position_and_vector;
  io_registers.a.MTX_IDENTITY = 0;

  io_registers.a.MTX_MODE = MTX_MODE__matrix_mode__texture;
  io_registers.a.MTX_IDENTITY = 0;
  io_registers.a.MTX_MODE = MTX_MODE__matrix_mode__position_and_vector;

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

  // normalized 45° vector
  int c = 0.57735 * 512;

  // lighting
  io_registers.a.LIGHT_VECTOR = 0
    | LIGHT_VECTOR__light_number(0)
    | LIGHT_VECTOR__decimal_z(-c)
    | LIGHT_VECTOR__decimal_y(-c)
    | LIGHT_VECTOR__decimal_x(-c);

  io_registers.a.LIGHT_VECTOR = 0
    | LIGHT_VECTOR__light_number(1)
    | LIGHT_VECTOR__decimal_z(-c)
    | LIGHT_VECTOR__decimal_y(-c)
    | LIGHT_VECTOR__decimal_x(c);

  io_registers.a.LIGHT_VECTOR = 0
    | LIGHT_VECTOR__light_number(2)
    | LIGHT_VECTOR__decimal_z(-c)
    | LIGHT_VECTOR__decimal_y(c)
    | LIGHT_VECTOR__decimal_x(-c);

  io_registers.a.LIGHT_COLOR = 0
    | LIGHT_COLOR__light_number(0)
    | LIGHT_COLOR__blue(31)
    | LIGHT_COLOR__green(31)
    | LIGHT_COLOR__red(31);

  io_registers.a.LIGHT_COLOR = 0
    | LIGHT_COLOR__light_number(1)
    | LIGHT_COLOR__blue(31)
    | LIGHT_COLOR__green(31)
    | LIGHT_COLOR__red(31);

  io_registers.a.LIGHT_COLOR = 0
    | LIGHT_COLOR__light_number(2)
    | LIGHT_COLOR__blue(31)
    | LIGHT_COLOR__green(31)
    | LIGHT_COLOR__red(31);

  // degrees
  int theta = 0;

  while (1) {
    // calculate sin/cos for 2d rotation; signed fp20.12 result
    int cos = cos_fp12(theta);
    int sin = sin_fp12(theta);

    int cos2 = cos_fp12(-theta >> 1);
    int sin2 = sin_fp12(-theta >> 1);

    io_registers.a.MTX_MODE = MTX_MODE__matrix_mode__position_and_vector;
    // reset position matrix
    io_registers.a.MTX_IDENTITY = 0;

    io_registers.a.MTX_TRANS = 0;
    io_registers.a.MTX_TRANS = (int)(-0.5 * (float)(1 << 12));
    io_registers.a.MTX_TRANS = 0;


    // multiply by a y-axis rotation
    io_registers.a.MTX_MULT_3X3 = cos2;
    io_registers.a.MTX_MULT_3X3 = 0;
    io_registers.a.MTX_MULT_3X3 = sin2;

    io_registers.a.MTX_MULT_3X3 = 0;
    io_registers.a.MTX_MULT_3X3 = 1 << 12;
    io_registers.a.MTX_MULT_3X3 = 0;

    io_registers.a.MTX_MULT_3X3 = -sin2;
    io_registers.a.MTX_MULT_3X3 = 0;
    io_registers.a.MTX_MULT_3X3 = cos2;

    /*
    // multiply by a z-axis rotation
    io_registers.a.MTX_MULT_3X3 = cos;
    io_registers.a.MTX_MULT_3X3 = -sin;
    io_registers.a.MTX_MULT_3X3 = 0;

    io_registers.a.MTX_MULT_3X3 = sin;
    io_registers.a.MTX_MULT_3X3 = cos;
    io_registers.a.MTX_MULT_3X3 = 0;

    io_registers.a.MTX_MULT_3X3 = 0;
    io_registers.a.MTX_MULT_3X3 = 0;
    io_registers.a.MTX_MULT_3X3 = 1 << 12;
    */

    // multiply by a x-axis rotation
    io_registers.a.MTX_MULT_3X3 = 1 << 12;
    io_registers.a.MTX_MULT_3X3 = 0;
    io_registers.a.MTX_MULT_3X3 = 0;

    io_registers.a.MTX_MULT_3X3 = 0;
    io_registers.a.MTX_MULT_3X3 = cos2;
    io_registers.a.MTX_MULT_3X3 = -sin2;

    io_registers.a.MTX_MULT_3X3 = 0;
    io_registers.a.MTX_MULT_3X3 = sin2;
    io_registers.a.MTX_MULT_3X3 = cos2;

    // cube faces

    io_registers.a.DIF_AMB = 0
      | DIF_AMB__ambient_blue(3)
      | DIF_AMB__ambient_green(3)
      | DIF_AMB__ambient_red(3)
      | DIF_AMB__diffuse_blue(10)
      | DIF_AMB__diffuse_green(10)
      | DIF_AMB__diffuse_red(10);

    io_registers.a.SPE_EMI = 0
      | SPE_EMI__specular_blue(25)
      | SPE_EMI__specular_green(25)
      | SPE_EMI__specular_red(25);

    /*
    io_registers.a.COLOR = 0
      | COLOR__blue(31)
      | COLOR__green(31)
      | COLOR__red(31);
    */

    // the following polygons are fully opaque; backface culling is
    // enabled
    io_registers.a.POLYGON_ATTR = 0
      | POLYGON_ATTR__polygon_id(0)
      | POLYGON_ATTR__alpha_value(31)
      | POLYGON_ATTR__render_front_surface__enable
      | POLYGON_ATTR__render_back_surface__enable
      | POLYGON_ATTR__polygon_mode__modulation
      | POLYGON_ATTR__light_2__enable
      | POLYGON_ATTR__light_1__enable
      | POLYGON_ATTR__light_0__enable;

    // the following vertices are a triangles

    io_registers.a.BEGIN_VTXS = BEGIN_VTXS__type__triangle;

    for (int oix = 0; oix < (sizeof (object)) / (sizeof (struct object *)); oix++) {
      struct object * obj = object[oix];
      const int num_triangles = obj->triangle_count;

      int material_ix = obj->material;
      int pixel_offset = material[material_ix].pixel.vram_offset;
      int palette_offset = material[material_ix].palette.vram_offset;
      int width = material[material_ix].pixel.width;
      int height = material[material_ix].pixel.height;
      int palette_size = material[material_ix].palette.palette_size;

      int shift = palette_size == 4 ? 3 : 4;
      io_registers.a.TEXPLTT_BASE = TEXPLTT_BASE__base_address(palette_offset >> shift);
      io_registers.a.TEXIMAGE_PARAM = 0
	| TEXIMAGE_PARAM__texture_coordinate_transformation_mode__texcoord_source
	| teximage_param__color_palette(palette_size)
	| TEXIMAGE_PARAM__repeat_t__repeat
	| TEXIMAGE_PARAM__repeat_s__repeat
	| teximage_param__t_size(height)
	| teximage_param__s_size(width)
	| TEXIMAGE_PARAM__texture_starting_address(pixel_offset >> 3);

      for (int i = 0; i < num_triangles; i++) {
	// "When texture mapping, the Geometry Engine works faster if you
	// issue commands in the following order: TexCoord→Normal→Vertex."
	struct vertex_texture * at = &majora_texture[obj->triangle[i].a.texture];
	// convert from UV space to ST space
	int au = at->u;
	int av = at->v;
	io_registers.a.TEXCOORD = 0
	  | TEXCOORD__t_coordinate(v_to_t(av, height))
	  | TEXCOORD__s_coordinate(u_to_s(au, width));

	struct vertex_normal * an = &majora_normal[obj->triangle[i].a.normal];
	io_registers.a.NORMAL = 0
	  | NORMAL__z_component(an->z)
	  | NORMAL__y_component(an->y)
	  | NORMAL__x_component(an->x);

	struct vertex_position * a = &majora_position[obj->triangle[i].a.position];
	io_registers.a.VTX_10 = 0
	  | VTX_10__z_coordinate(a->z)
	  | VTX_10__y_coordinate(a->y)
	  | VTX_10__x_coordinate(a->x);

	struct vertex_texture * bt = &majora_texture[obj->triangle[i].b.texture];
	// convert from UV space to ST space
	int bu = bt->u;
	int bv = bt->v;
	io_registers.a.TEXCOORD = 0
	  | TEXCOORD__t_coordinate(v_to_t(bv, height))
	  | TEXCOORD__s_coordinate(u_to_s(bu, width));

	struct vertex_normal * bn = &majora_normal[obj->triangle[i].b.normal];
	io_registers.a.NORMAL = 0
	  | NORMAL__z_component(bn->z)
	  | NORMAL__y_component(bn->y)
	  | NORMAL__x_component(bn->x);

	struct vertex_position * b = &majora_position[obj->triangle[i].b.position];
	io_registers.a.VTX_10 = 0
	  | VTX_10__z_coordinate(b->z)
	  | VTX_10__y_coordinate(b->y)
	  | VTX_10__x_coordinate(b->x);

	struct vertex_texture * ct = &majora_texture[obj->triangle[i].c.texture];
	// convert from UV space to ST space
	int cu = ct->u;
	int cv = ct->v;
	io_registers.a.TEXCOORD = 0
	  | TEXCOORD__t_coordinate(v_to_t(cv, height))
	  | TEXCOORD__s_coordinate(u_to_s(cu, width));

	struct vertex_normal * cn = &majora_normal[obj->triangle[i].c.normal];
	io_registers.a.NORMAL = 0
	  | NORMAL__z_component(cn->z)
	  | NORMAL__y_component(cn->y)
	  | NORMAL__x_component(cn->x);

	struct vertex_position * c = &majora_position[obj->triangle[i].c.position];
	io_registers.a.VTX_10 = 0
	  | VTX_10__z_coordinate(c->z)
	  | VTX_10__y_coordinate(c->y)
	  | VTX_10__x_coordinate(c->x);
      }

    }

    // end of the triangle
    io_registers.a.END_VTXS = 0;

    // wait for the geometry engine
    while (io_registers.a.GXSTAT & GXSTAT__geometry_engine_busy);

    // wait for the end of the current frame
    while (io_registers.a.VCOUNT != 262);
    while (io_registers.a.VCOUNT == 262);

    // swap buffers
    io_registers.a.SWAP_BUFFERS = 0;

    // increment theta once per frame
    theta += 1;
    if (theta >= 360 * 16) {
      theta = 0;
    }
  }
}
