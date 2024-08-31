#pragma once

#include "graphics_engine_a.h"
#include "graphics_engine_b.h"

struct io_registers {
  struct graphics_engine_a a;
  struct graphics_engine_b b;
};

extern struct io_registers io_registers __asm("io_registers");
