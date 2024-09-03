#include "io_registers.h"
#include "bits.h"

#include "math.h"

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

  // clear matrix stack status
  io_registers.a.GXSTAT |= GXSTAT__matrix_stack_status__overflow_or_underflow;

  // load identity matrices
  io_registers.a.MTX_MODE = MTX_MODE__matrix_mode__projection;
  io_registers.a.MTX_IDENTITY = 0;
  // scale the x-axis by the ratio of the display height by the display width.
  io_registers.a.MTX_SCALE = (192 << 12) / 256;
  io_registers.a.MTX_SCALE = 1 << 12;
  io_registers.a.MTX_SCALE = 1 << 12;

  io_registers.a.MTX_MODE = MTX_MODE__matrix_mode__position;
  io_registers.a.MTX_IDENTITY = 0;

  io_registers.a.MTX_MODE = MTX_MODE__matrix_mode__position_and_vector;
  io_registers.a.MTX_IDENTITY = 0;

  // disable all 3d effects
  io_registers.a.DISP3DCNT = 0
    | DISP3DCNT__clear_image__disable
    | DISP3DCNT__fog_master__disable
    | DISP3DCNT__edge_marking__disable
    | DISP3DCNT__anti_aliasing__disable
    | DISP3DCNT__alpha_blending__disable
    | DISP3DCNT__alpha_test__disable
    | DISP3DCNT__texture_mapping__disable;

  // set the 3d clear color to a dark red
  io_registers.a.CLEAR_COLOR = 0
    | CLEAR_COLOR__clear_polygon_id(31)
    | CLEAR_COLOR__alpha_value(31)
    | CLEAR_COLOR__blue(1)
    | CLEAR_COLOR__green(1)
    | CLEAR_COLOR__red(10);

  // set the depth buffer clear value to the maximum value
  io_registers.a.CLEAR_DEPTH = CLEAR_DEPTH__value(0x7fff);

  // the following polygons are fully opaque and are not
  // backface-culled
  io_registers.a.POLYGON_ATTR = 0
    | POLYGON_ATTR__alpha_value(31)
    | POLYGON_ATTR__render_front_surface__enable
    | POLYGON_ATTR__render_back_surface__enable;

  // the 3d viewport is the entire display area
  io_registers.a.VIEWPORT = 0
    | VIEWPORT__y2(191)
    | VIEWPORT__x2(255)
    | VIEWPORT__y1(0)
    | VIEWPORT__x1(0);

  // VTX_10 uses signed 4.6 floating point (10 bit)
  // | 9 | 8 7 6 | 5 4 3 2 1 0 |
  // | s |  int  | decimal     |
  int fixed_point_divisor = 64; // == 2⁶

  // equilateral triangle; centered around the display origin in NDC
  /*
        A
       / \
      B---C

   */

  // fixed point constants; these are converted from floating-point to
  // integer at compile-time
  int ax =  0.0           * fixed_point_divisor;
  int ay =  1.0           * fixed_point_divisor;

  int bx = -0.86602540378 * fixed_point_divisor; // - sqrt(3) / 2
  int by = -0.5           * fixed_point_divisor;

  int cx =  0.86602540378 * fixed_point_divisor; // + sqrt(3) / 2
  int cy = -0.5           * fixed_point_divisor;

  int  z =  1.0           * fixed_point_divisor;

  // degrees
  int theta = 0;

  while (1) {
    // calculate sin/cos for 2d rotation; signed fp20.12 result
    int cos = cos_fp12(theta);
    int sin = sin_fp12(theta);

    // load this 4x3 rotation matrix:
    //
    // | cos(θ)  -sin(θ)     0 |
    // | sin(θ)   cos(θ)     0 |
    // |     0        0      1 |
    // |     0        0      0 |
    //
    // the 4x3 matrix load order is:
    //
    // | 0 1 2 |
    // | 3 4 5 |
    // | 6 7 8 |
    // | 9 a b |

    io_registers.a.MTX_MODE = MTX_MODE__matrix_mode__position;
    io_registers.a.MTX_LOAD_4X3 = cos;     // 0
    io_registers.a.MTX_LOAD_4X3 = -sin;    // 1
    io_registers.a.MTX_LOAD_4X3 = 0;       // 2

    io_registers.a.MTX_LOAD_4X3 = sin;     // 3
    io_registers.a.MTX_LOAD_4X3 = cos;     // 4
    io_registers.a.MTX_LOAD_4X3 = 0;       // 5

    io_registers.a.MTX_LOAD_4X3 = 0;       // 6
    io_registers.a.MTX_LOAD_4X3 = 0;       // 7
    io_registers.a.MTX_LOAD_4X3 = 1 << 12; // 8

    io_registers.a.MTX_LOAD_4X3 = 0;       // 9
    io_registers.a.MTX_LOAD_4X3 = 0;       // a
    io_registers.a.MTX_LOAD_4X3 = 0;       // b

    // the following vertices are a triangle
    io_registers.a.BEGIN_VTXS = BEGIN_VTXS__type__triangle;

    io_registers.a.COLOR = COLOR__blue(31);
    io_registers.a.VTX_10 = 0
      | VTX_10__z_coordinate(z)
      | VTX_10__y_coordinate(ay)
      | VTX_10__x_coordinate(ax);

    io_registers.a.COLOR = COLOR__green(31);
    io_registers.a.VTX_10 = 0
      | VTX_10__z_coordinate(z)
      | VTX_10__y_coordinate(by)
      | VTX_10__x_coordinate(bx);

    io_registers.a.COLOR = COLOR__red(31);
    io_registers.a.VTX_10 = 0
      | VTX_10__z_coordinate(z)
      | VTX_10__y_coordinate(cy)
      | VTX_10__x_coordinate(cx);

    // end of the triangle
    io_registers.a.END_VTXS = 0;

    // wait for the geomtry engine
    while (io_registers.a.GXSTAT & GXSTAT__geometry_engine_busy);

    // wait for the end of the current frame
    while (io_registers.a.VCOUNT != 262);
    while (io_registers.a.VCOUNT == 262);

    // swap buffers
    io_registers.a.SWAP_BUFFERS = 0;

    // increment theta once per frame
    theta += 1;
    if (theta >= 360) {
      theta = 0;
    }
  }
}
