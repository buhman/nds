#pragma once

#include <stdint.h>

#include "model/material.h"

enum material {
  mtl_060067E0,
  mtl_060077E0,
  mtl_060079E0,
  mtl_06007BE0,
  mtl_06007DE0,
  mtl_06007FE0,
};

struct material_descriptor material[] = {
  [mtl_060067E0] = {
    .pixel = {
      .start = (uint8_t *)&_binary_060067E0_data_start,
      .size = (int)&_binary_060067E0_data_size,
      .vram_offset = 0,
      .width = 64,
      .height = 64,
    },
    .palette = {
      .start = (uint8_t *)&_binary_060067E0_data_pal_start,
      .size = (int)&_binary_060067E0_data_pal_size,
      .vram_offset = 0,
      .palette_size = 256,
    },
  },
  [mtl_060077E0] = {
    .pixel = {
      .start = (uint8_t *)&_binary_060077E0_data_start,
      .size = (int)&_binary_060077E0_data_size,
      .vram_offset = 4096,
      .width = 16,
      .height = 16,
    },
    .palette = {
      .start = (uint8_t *)&_binary_060077E0_data_pal_start,
      .size = (int)&_binary_060077E0_data_pal_size,
      .vram_offset = 512,
      .palette_size = 4,
    },
  },
  [mtl_060079E0] = {
    .pixel = {
      .start = (uint8_t *)&_binary_060079E0_data_start,
      .size = (int)&_binary_060079E0_data_size,
      .vram_offset = 4160,
      .width = 16,
      .height = 16,
    },
    .palette = {
      .start = (uint8_t *)&_binary_060079E0_data_pal_start,
      .size = (int)&_binary_060079E0_data_pal_size,
      .vram_offset = 528,
      .palette_size = 4,
    },
  },
  [mtl_06007BE0] = {
    .pixel = {
      .start = (uint8_t *)&_binary_06007BE0_data_start,
      .size = (int)&_binary_06007BE0_data_size,
      .vram_offset = 4224,
      .width = 16,
      .height = 16,
    },
    .palette = {
      .start = (uint8_t *)&_binary_06007BE0_data_pal_start,
      .size = (int)&_binary_06007BE0_data_pal_size,
      .vram_offset = 544,
      .palette_size = 4,
    },
  },
  [mtl_06007DE0] = {
    .pixel = {
      .start = (uint8_t *)&_binary_06007DE0_data_start,
      .size = (int)&_binary_06007DE0_data_size,
      .vram_offset = 4288,
      .width = 16,
      .height = 16,
    },
    .palette = {
      .start = (uint8_t *)&_binary_06007DE0_data_pal_start,
      .size = (int)&_binary_06007DE0_data_pal_size,
      .vram_offset = 560,
      .palette_size = 16,
    },
  },
  [mtl_06007FE0] = {
    .pixel = {
      .start = (uint8_t *)&_binary_06007FE0_data_start,
      .size = (int)&_binary_06007FE0_data_size,
      .vram_offset = 4416,
      .width = 32,
      .height = 32,
    },
    .palette = {
      .start = (uint8_t *)&_binary_06007FE0_data_pal_start,
      .size = (int)&_binary_06007FE0_data_pal_size,
      .vram_offset = 592,
      .palette_size = 256,
    },
  },
};

