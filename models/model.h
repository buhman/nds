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
  uint16_t x;
  uint16_t y;
  uint16_t z;
};

struct vertex_normal { // s.9 fixed point
  uint16_t x;
  uint16_t y;
  uint16_t z;
};

struct vertex_texture { // s.15 fixed point
  uint16_t u;
  uint16_t v;
};
