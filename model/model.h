#pragma once

#include <stdint.h>

struct index_ptn {
  uint16_t position;
  uint16_t texture;
  uint16_t normal;
};

union triangle {
  struct {
    struct index_ptn a;
    struct index_ptn b;
    struct index_ptn c;
  };
  struct index_ptn v[3];
};

union quadrilateral {
  struct {
    struct index_ptn a;
    struct index_ptn b;
    struct index_ptn c;
    struct index_ptn d;
  };
  struct index_ptn v[4];
};

struct vertex_position { // signed 4.6 fixed point
  int16_t x;
  int16_t y;
  int16_t z;
};

struct vertex_normal { // s.9 fixed point
  int16_t x;
  int16_t y;
  int16_t z;
};

struct vertex_texture { // s.15 fixed point
  int16_t u;
  int16_t v;
};

typedef struct vertex_position vertex_position;
typedef struct vertex_normal vertex_normal;
typedef struct vertex_texture vertex_texture;

struct object {
  union triangle * triangle;
  union quadrilateral * quadrilateral;
  int triangle_count;
  int quadrilateral_count;
  int material;
};

struct model {
  vertex_position * position;
  vertex_texture * texture;
  vertex_normal * normal;

  struct object ** object;
  int object_count;
};
