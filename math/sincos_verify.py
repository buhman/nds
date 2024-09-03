from math import cos, sin

import sys
from gen_cos_table import fixed_point_bits, divisor, tau

for i in range(-360, 360 + 1):
    line = sys.stdin.readline()
    ix, value = map(int, line.strip().split())
    assert i == ix
    radians = i / 360 * tau
    n = sin(radians)
    integer = round(n)
    decimal = round((n - integer) * divisor)
    fixed_point = (integer * divisor) + decimal
    if fixed_point != value:
        print("error", i, fixed_point, value)
