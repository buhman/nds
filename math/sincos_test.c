#include <stdio.h>

#include "math.h"

int main()
{
  for (int i = -360; i <= 360; i++) {
    printf("%d %d\n", i, sin_fp12(i));
  }
}
