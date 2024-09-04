#include "io_registers.h"
#include "bits.h"

#include "models/cube.h"
#include "math/math.h"

static const uint16_t face_colors[6] = {
  COLOR__blue(31),
  COLOR__red(31),
  COLOR__green(31),
  COLOR__red(31) | COLOR__green(31),
  COLOR__red(31) | COLOR__blue(31),
  COLOR__green(31) | COLOR__blue(31),
};

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
    | DISP3DCNT__texture_mapping__disable;

  // clear matrix stack status
  io_registers.a.GXSTAT |= GXSTAT__matrix_stack_status__overflow_or_underflow;

  // load identity matrices
  io_registers.a.MTX_MODE = MTX_MODE__matrix_mode__projection;
  io_registers.a.MTX_IDENTITY = 0;

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
  io_registers.a.MTX_TRANS = -3 << 12;

  io_registers.a.MTX_MODE = MTX_MODE__matrix_mode__position;
  io_registers.a.MTX_IDENTITY = 0;

  io_registers.a.MTX_MODE = MTX_MODE__matrix_mode__position_and_vector;
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

  // the following polygons are fully opaque; backface culling is
  // enabled
  io_registers.a.POLYGON_ATTR = 0
    | POLYGON_ATTR__alpha_value(31)
    | POLYGON_ATTR__render_front_surface__enable;

  // the 3d viewport is the entire display area
  io_registers.a.VIEWPORT = 0
    | VIEWPORT__y2(191)
    | VIEWPORT__x2(255)
    | VIEWPORT__y1(0)
    | VIEWPORT__x1(0);

  // degrees
  int theta = 0;

  while (1) {
    // calculate sin/cos for 2d rotation; signed fp20.12 result
    int cos = cos_fp12(theta);
    int sin = sin_fp12(theta);

    int cos2 = cos_fp12(theta >> 1);
    int sin2 = sin_fp12(theta >> 1);

    io_registers.a.MTX_MODE = MTX_MODE__matrix_mode__position;
    // reset position matrix
    io_registers.a.MTX_IDENTITY = 0;

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

    // multiply by a x-axis rotation
    io_registers.a.MTX_MULT_3X3 = cos2;
    io_registers.a.MTX_MULT_3X3 = -sin2;
    io_registers.a.MTX_MULT_3X3 = 0;

    io_registers.a.MTX_MULT_3X3 = sin2;
    io_registers.a.MTX_MULT_3X3 = cos2;
    io_registers.a.MTX_MULT_3X3 = 0;

    io_registers.a.MTX_MULT_3X3 = 0;
    io_registers.a.MTX_MULT_3X3 = 0;
    io_registers.a.MTX_MULT_3X3 = 1 << 12;

    // the following vertices are a quadrilateral
    io_registers.a.BEGIN_VTXS = BEGIN_VTXS__type__quadrilateral;

    // cube faces
    for (int i = 0; i < 6; i++) {
      io_registers.a.COLOR = face_colors[i];

      struct vertex_position * a = &cube_positions[cube_faces[i].a.position];
      io_registers.a.VTX_10 = 0
	| VTX_10__z_coordinate(a->z)
	| VTX_10__y_coordinate(a->y)
	| VTX_10__x_coordinate(a->x);

      struct vertex_position * b = &cube_positions[cube_faces[i].b.position];
      io_registers.a.VTX_10 = 0
	| VTX_10__z_coordinate(b->z)
	| VTX_10__y_coordinate(b->y)
	| VTX_10__x_coordinate(b->x);

      struct vertex_position * c = &cube_positions[cube_faces[i].c.position];
      io_registers.a.VTX_10 = 0
	| VTX_10__z_coordinate(c->z)
	| VTX_10__y_coordinate(c->y)
	| VTX_10__x_coordinate(c->x);

      struct vertex_position * d = &cube_positions[cube_faces[i].d.position];
      io_registers.a.VTX_10 = 0
	| VTX_10__z_coordinate(d->z)
	| VTX_10__y_coordinate(d->y)
	| VTX_10__x_coordinate(d->x);
    }

    // end of the quadrilateral
    io_registers.a.END_VTXS = 0;

    // wait for the end of the current frame
    while (io_registers.a.VCOUNT != 262);
    while (io_registers.a.VCOUNT == 262);

    // wait for the geometry engine
    while (io_registers.a.GXSTAT & GXSTAT__geometry_engine_busy);

    // swap buffers
    io_registers.a.SWAP_BUFFERS = 0;

    // increment theta once per frame
    theta += 1;
    if (theta >= 360 * 2) {
      theta = 0;
    }
  }
}
