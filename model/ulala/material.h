#pragma once

#include <stdint.h>

#include "model/material.h"

enum material {
  eye,
  ha,
  p03b_hair,
  p_face,
  p_nomal_mix,
  p_ref_or,
  u_lb,
};

struct material_descriptor material[] = {
  [eye] = {
    .pixel = {
      .start = (uint8_t *)&_binary_eye_data_start,
      .size = (int)&_binary_eye_data_size,
      .vram_offset = 0,
      .width = 64,
      .height = 64,
    },
    .palette = {
      .start = (uint8_t *)&_binary_eye_data_pal_start,
      .size = (int)&_binary_eye_data_pal_size,
      .vram_offset = 0,
      .palette_size = 256,
    },
  },
  [ha] = {
    .pixel = {
      .start = (uint8_t *)&_binary_ha_data_start,
      .size = (int)&_binary_ha_data_size,
      .vram_offset = 4096,
      .width = 32,
      .height = 32,
    },
    .palette = {
      .start = (uint8_t *)&_binary_ha_data_pal_start,
      .size = (int)&_binary_ha_data_pal_size,
      .vram_offset = 368,
      .palette_size = 256,
    },
  },
  [p03b_hair] = {
    .pixel = {
      .start = (uint8_t *)&_binary_p03b_hair_data_start,
      .size = (int)&_binary_p03b_hair_data_size,
      .vram_offset = 5120,
      .width = 64,
      .height = 64,
    },
    .palette = {
      .start = (uint8_t *)&_binary_p03b_hair_data_pal_start,
      .size = (int)&_binary_p03b_hair_data_pal_size,
      .vram_offset = 464,
      .palette_size = 256,
    },
  },
  [p_face] = {
    .pixel = {
      .start = (uint8_t *)&_binary_p_face_data_start,
      .size = (int)&_binary_p_face_data_size,
      .vram_offset = 9216,
      .width = 256,
      .height = 256,
    },
    .palette = {
      .start = (uint8_t *)&_binary_p_face_data_pal_start,
      .size = (int)&_binary_p_face_data_pal_size,
      .vram_offset = 560,
      .palette_size = 256,
    },
  },
  [p_nomal_mix] = {
    .pixel = {
      .start = (uint8_t *)&_binary_p_nomal_mix_data_start,
      .size = (int)&_binary_p_nomal_mix_data_size,
      .vram_offset = 74752,
      .width = 128,
      .height = 128,
    },
    .palette = {
      .start = (uint8_t *)&_binary_p_nomal_mix_data_pal_start,
      .size = (int)&_binary_p_nomal_mix_data_pal_size,
      .vram_offset = 1072,
      .palette_size = 256,
    },
  },
  [p_ref_or] = {
    .pixel = {
      .start = (uint8_t *)&_binary_p_ref_or_data_start,
      .size = (int)&_binary_p_ref_or_data_size,
      .vram_offset = 91136,
      .width = 64,
      .height = 64,
    },
    .palette = {
      .start = (uint8_t *)&_binary_p_ref_or_data_pal_start,
      .size = (int)&_binary_p_ref_or_data_pal_size,
      .vram_offset = 1472,
      .palette_size = 4,
    },
  },
  [u_lb] = {
    .pixel = {
      .start = (uint8_t *)&_binary_u_lb_data_start,
      .size = (int)&_binary_u_lb_data_size,
      .vram_offset = 92160,
      .width = 64,
      .height = 64,
    },
    .palette = {
      .start = (uint8_t *)&_binary_u_lb_data_pal_start,
      .size = (int)&_binary_u_lb_data_pal_size,
      .vram_offset = 1488,
      .palette_size = 256,
    },
  },
};

