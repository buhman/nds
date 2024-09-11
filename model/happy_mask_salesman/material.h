#pragma once

#include <stdint.h>

#include "model/material.h"

enum material {
  material_001D075B,
  material_0033AD02,
  material_0059BDCE,
  material_00650E52,
  material_007F0EC7,
  material_01054239,
  material_012F5405,
  material_0194E6CE,
  material_01D11516,
  material_01D11516_001,
  material_01F419A5,
  material_023C1D43,
  material_0327AC42,
  material_038D80E9,
  material_03C5C9F5,
  material_03F98837,
};

struct material_descriptor material[] = {
  [material_001D075B] = {
    .pixel = {
      .start = (uint8_t *)&_binary_mask_07_C200_data_start,
      .size = (int)&_binary_mask_07_C200_data_size,
      .vram_offset = 0,
      .width = 32,
      .height = 64,
    },
    .palette = {
      .start = (uint8_t *)&_binary_mask_07_C200_data_pal_start,
      .size = (int)&_binary_mask_07_C200_data_pal_size,
      .vram_offset = 0,
      .palette_size = 256,
    },
  },
  [material_0033AD02] = {
    .pixel = {
      .start = (uint8_t *)&_binary_maskmaster_00_0_data_start,
      .size = (int)&_binary_maskmaster_00_0_data_size,
      .vram_offset = 2048,
      .width = 128,
      .height = 128,
    },
    .palette = {
      .start = (uint8_t *)&_binary_maskmaster_00_0_data_pal_start,
      .size = (int)&_binary_maskmaster_00_0_data_pal_size,
      .vram_offset = 512,
      .palette_size = 256,
    },
  },
  [material_0059BDCE] = {
    .pixel = {
      .start = (uint8_t *)&_binary_maskmaster_e00_6A00_data_start,
      .size = (int)&_binary_maskmaster_e00_6A00_data_size,
      .vram_offset = 18432,
      .width = 32,
      .height = 64,
    },
    .palette = {
      .start = (uint8_t *)&_binary_maskmaster_e00_6A00_data_pal_start,
      .size = (int)&_binary_maskmaster_e00_6A00_data_pal_size,
      .vram_offset = 1024,
      .palette_size = 256,
    },
  },
  [material_00650E52] = {
    .pixel = {
      .start = (uint8_t *)&_binary_mask_00_8A00_data_start,
      .size = (int)&_binary_mask_00_8A00_data_size,
      .vram_offset = 20480,
      .width = 32,
      .height = 64,
    },
    .palette = {
      .start = (uint8_t *)&_binary_mask_00_8A00_data_pal_start,
      .size = (int)&_binary_mask_00_8A00_data_pal_size,
      .vram_offset = 1424,
      .palette_size = 256,
    },
  },
  [material_007F0EC7] = {
    .pixel = {
      .start = (uint8_t *)&_binary_maskmaster_00_0_data_start,
      .size = (int)&_binary_maskmaster_00_0_data_size,
      .vram_offset = 22528,
      .width = 128,
      .height = 128,
    },
    .palette = {
      .start = (uint8_t *)&_binary_maskmaster_00_0_data_pal_start,
      .size = (int)&_binary_maskmaster_00_0_data_pal_size,
      .vram_offset = 1936,
      .palette_size = 256,
    },
  },
  [material_01054239] = {
    .pixel = {
      .start = (uint8_t *)&_binary_mask_08_CA00_data_start,
      .size = (int)&_binary_mask_08_CA00_data_size,
      .vram_offset = 38912,
      .width = 32,
      .height = 64,
    },
    .palette = {
      .start = (uint8_t *)&_binary_mask_08_CA00_data_pal_start,
      .size = (int)&_binary_mask_08_CA00_data_pal_size,
      .vram_offset = 2448,
      .palette_size = 256,
    },
  },
  [material_012F5405] = {
    .pixel = {
      .start = (uint8_t *)&_binary_mask_09_D200_data_start,
      .size = (int)&_binary_mask_09_D200_data_size,
      .vram_offset = 40960,
      .width = 32,
      .height = 64,
    },
    .palette = {
      .start = (uint8_t *)&_binary_mask_09_D200_data_pal_start,
      .size = (int)&_binary_mask_09_D200_data_pal_size,
      .vram_offset = 2960,
      .palette_size = 256,
    },
  },
  [material_0194E6CE] = {
    .pixel = {
      .start = (uint8_t *)&_binary_mask_05_B200_data_start,
      .size = (int)&_binary_mask_05_B200_data_size,
      .vram_offset = 43008,
      .width = 32,
      .height = 64,
    },
    .palette = {
      .start = (uint8_t *)&_binary_mask_05_B200_data_pal_start,
      .size = (int)&_binary_mask_05_B200_data_pal_size,
      .vram_offset = 3472,
      .palette_size = 256,
    },
  },
  [material_01D11516] = {
    .pixel = {
      .start = (uint8_t *)&_binary_maskmaster_01_4A00_data_start,
      .size = (int)&_binary_maskmaster_01_4A00_data_size,
      .vram_offset = 45056,
      .width = 128,
      .height = 128,
    },
    .palette = {
      .start = (uint8_t *)&_binary_maskmaster_01_4A00_data_pal_start,
      .size = (int)&_binary_maskmaster_01_4A00_data_pal_size,
      .vram_offset = 3984,
      .palette_size = 256,
    },
  },
  [material_01D11516_001] = {
    .pixel = {
      .start = (uint8_t *)&_binary_maskmaster_01_4A00_data_start,
      .size = (int)&_binary_maskmaster_01_4A00_data_size,
      .vram_offset = 61440,
      .width = 128,
      .height = 128,
    },
    .palette = {
      .start = (uint8_t *)&_binary_maskmaster_01_4A00_data_pal_start,
      .size = (int)&_binary_maskmaster_01_4A00_data_pal_size,
      .vram_offset = 4496,
      .palette_size = 256,
    },
  },
  [material_01F419A5] = {
    .pixel = {
      .start = (uint8_t *)&_binary_mask_04_AA00_data_start,
      .size = (int)&_binary_mask_04_AA00_data_size,
      .vram_offset = 77824,
      .width = 32,
      .height = 64,
    },
    .palette = {
      .start = (uint8_t *)&_binary_mask_04_AA00_data_pal_start,
      .size = (int)&_binary_mask_04_AA00_data_pal_size,
      .vram_offset = 5008,
      .palette_size = 256,
    },
  },
  [material_023C1D43] = {
    .pixel = {
      .start = (uint8_t *)&_binary_mask_06_BA00_data_start,
      .size = (int)&_binary_mask_06_BA00_data_size,
      .vram_offset = 79872,
      .width = 32,
      .height = 64,
    },
    .palette = {
      .start = (uint8_t *)&_binary_mask_06_BA00_data_pal_start,
      .size = (int)&_binary_mask_06_BA00_data_pal_size,
      .vram_offset = 5520,
      .palette_size = 256,
    },
  },
  [material_0327AC42] = {
    .pixel = {
      .start = (uint8_t *)&_binary_maskmaster_m00_7A00_data_start,
      .size = (int)&_binary_maskmaster_m00_7A00_data_size,
      .vram_offset = 81920,
      .width = 64,
      .height = 32,
    },
    .palette = {
      .start = (uint8_t *)&_binary_maskmaster_m00_7A00_data_pal_start,
      .size = (int)&_binary_maskmaster_m00_7A00_data_pal_size,
      .vram_offset = 6032,
      .palette_size = 256,
    },
  },
  [material_038D80E9] = {
    .pixel = {
      .start = (uint8_t *)&_binary_mask_01_9200_data_start,
      .size = (int)&_binary_mask_01_9200_data_size,
      .vram_offset = 83968,
      .width = 32,
      .height = 64,
    },
    .palette = {
      .start = (uint8_t *)&_binary_mask_01_9200_data_pal_start,
      .size = (int)&_binary_mask_01_9200_data_pal_size,
      .vram_offset = 6544,
      .palette_size = 256,
    },
  },
  [material_03C5C9F5] = {
    .pixel = {
      .start = (uint8_t *)&_binary_mask_03_A200_data_start,
      .size = (int)&_binary_mask_03_A200_data_size,
      .vram_offset = 86016,
      .width = 32,
      .height = 64,
    },
    .palette = {
      .start = (uint8_t *)&_binary_mask_03_A200_data_pal_start,
      .size = (int)&_binary_mask_03_A200_data_pal_size,
      .vram_offset = 7056,
      .palette_size = 256,
    },
  },
  [material_03F98837] = {
    .pixel = {
      .start = (uint8_t *)&_binary_mask_02_9A00_data_start,
      .size = (int)&_binary_mask_02_9A00_data_size,
      .vram_offset = 88064,
      .width = 32,
      .height = 64,
    },
    .palette = {
      .start = (uint8_t *)&_binary_mask_02_9A00_data_pal_start,
      .size = (int)&_binary_mask_02_9A00_data_pal_size,
      .vram_offset = 7568,
      .palette_size = 256,
    },
  },
};

