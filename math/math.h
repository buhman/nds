#pragma once

#define abs __builtin_abs

int cos_fp12(int theta);

static inline int sin_fp12(int theta)
{
  return cos_fp12(theta - 90);
}
