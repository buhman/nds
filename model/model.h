#pragma once

#include <stdint.h>

struct index_ptn {
  uint16_t position;
  uint16_t texture;
  uint16_t normal;
};

struct triangle {
  struct index_ptn a;
  struct index_ptn b;
  struct index_ptn c;
};

struct quadrilateral {
  struct index_ptn a;
  struct index_ptn b;
  struct index_ptn c;
  struct index_ptn d;
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

struct object {
  struct triangle * triangle;
  struct quadrilateral * quadrilateral;
  int triangle_count;
  int quadrilateral_count;
  int material;
};
