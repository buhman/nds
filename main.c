#include "registers/graphics_engine_a.h"

void main()
{
  graphics_engine_a.DISPCNT = (1 << 16); // DISPLAY_ON

  // palette ram
  *((volatile uint16_t *)(0x05000000)) = (7 << 10) | (31 << 5) | (19 << 0);
}
