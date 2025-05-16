#pragma once

#include <stddef.h>

#include "model.h"

// 3.6 fixed-point
const vertex_position cube_position[] = {
  {64, 64, -64},
  {64, -64, -64},
  {64, 64, 64},
  {64, -64, 64},
  {-64, 64, -64},
  {-64, -64, -64},
  {-64, 64, 64},
  {-64, -64, 64},
};

// 1.14 fixed-point
const vertex_texture cube_texture[] = {
  {16384, 16384},
  {0, 16384},
  {0, 0},
  {16384, 0},
};

// 0.9 fixed-point
const vertex_normal cube_normal[] = {
  {0, 512, 0},
  {0, 0, 512},
  {-512, 0, 0},
  {0, -512, 0},
  {512, 0, 0},
  {0, 0, -512},
};

const union quadrilateral cube_Cube_quadrilateral[] = {
  { .v = {
    {0, 0, 0},
    {4, 1, 0},
    {6, 2, 0},
    {2, 3, 0},
  }},
  { .v = {
    {3, 3, 1},
    {2, 0, 1},
    {6, 1, 1},
    {7, 2, 1},
  }},
  { .v = {
    {7, 2, 2},
    {6, 1, 2},
    {4, 0, 2},
    {5, 3, 2},
  }},
  { .v = {
    {5, 1, 3},
    {1, 0, 3},
    {3, 3, 3},
    {7, 2, 3},
  }},
  { .v = {
    {1, 3, 4},
    {0, 0, 4},
    {2, 1, 4},
    {3, 2, 4},
  }},
  { .v = {
    {5, 2, 5},
    {4, 1, 5},
    {0, 0, 5},
    {1, 3, 5},
  }},
};

const struct object cube_Cube = {
  .triangle = NULL,
  .quadrilateral = &cube_Cube_quadrilateral[0],
  .triangle_count = 0,
  .quadrilateral_count = 6,
  .material = -1,
};

const struct object * cube_object_list[] = {
  &cube_Cube,
};

const struct model cube_model = {
  .position = &cube_position[0],
  .texture = &cube_texture[0],
  .normal = &cube_normal[0],
  .object = &cube_object_list[0],
  .object_count = 1,
};
