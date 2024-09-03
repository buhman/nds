#include <stdint.h>

#include "math.h"

extern const uint16_t cos_table_fp12[];

int cos_fp12(int theta)
{
  theta = abs(theta);
  while (theta > 360) {
    theta -= 360;
  }

  if (theta <= 90) {
    return cos_table_fp12[theta];
  } else if (theta <= 180) {
    return - cos_table_fp12[180 - theta];
  } else if (theta <= 270) {
    return - cos_table_fp12[theta - 180];
  } else {
    return cos_table_fp12[360 - theta];
  }
}
