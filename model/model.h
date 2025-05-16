#pragma once

#include <stdint.h>

struct index_ptn {
  const uint16_t position;
  const uint16_t texture;
  const uint16_t normal;
};

union triangle {
  struct {
    const struct index_ptn a;
    const struct index_ptn b;
    const struct index_ptn c;
  };
  const struct index_ptn v[3];
};

union quadrilateral {
  struct {
    const struct index_ptn a;
    const struct index_ptn b;
    const struct index_ptn c;
    const struct index_ptn d;
  };
  const struct index_ptn v[4];
};

struct vertex_position { // signed 4.6 fixed point
  const int16_t x;
  const int16_t y;
  const int16_t z;
};

struct vertex_normal { // s.9 fixed point
  const int16_t x;
  const int16_t y;
  const int16_t z;
};

struct vertex_texture { // s.15 fixed point
  const int16_t u;
  const int16_t v;
};

typedef struct vertex_position vertex_position;
typedef struct vertex_normal vertex_normal;
typedef struct vertex_texture vertex_texture;

struct object {
  const union triangle * triangle;
  const union quadrilateral * quadrilateral;
  const int triangle_count;
  const int quadrilateral_count;
  const int material;
};

struct model {
  const vertex_position * position;
  const vertex_texture * texture;
  const vertex_normal * normal;

  const struct object ** object;
  const int object_count;
};
