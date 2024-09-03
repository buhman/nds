from math import cos, pi

fixed_point_bits = 12
divisor = 2 ** fixed_point_bits
tau = pi * 2

if __name__ == "__main__":
    print("#include <stdint.h>")
    print()
    print(f"const uint16_t cos_table_fp{fixed_point_bits}[91] = {{")
    for i in range(0, 91):
        radians = i / 360 * tau
        n = cos(radians)
        assert n >= 0
        integer = round(n)
        decimal = round((n - integer) * divisor)
        assert decimal < divisor
        fixed_point = (integer * divisor) + decimal
        comma = "" if i == 90 else ","
        print(f"  {fixed_point}{comma}")
    print("};")
