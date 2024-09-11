from dataclasses import dataclass
import string

class FixedPointOverflow(Exception):
    pass

@dataclass
class FixedPoint:
    sign: int
    value: int
    point: int

    def to_fixed_point(fp, integer_bits, fraction_bits):
        point = 1 << fraction_bits
        value = (fp.value * point) // fp.point
        if integer_bits is not None:
            integer_point = 1 << integer_bits
            integer = value // point
            if integer >= integer_point:
                raise FixedPointOverflow((integer, integer_point))
        return FixedPoint(
            fp.sign,
            value,
            point
        )

    def to_int(fp):
        return fp.sign * fp.value

    def to_float(fp):
        return fp.sign * fp.value / fp.point

def from_float(n):
    if n == 0.0:
        sign = 1
        value = 0
    else:
        sign = -1 if n < 0 else 1
        value = abs(round(n * (2 ** 32)))
    point = 2 ** 32
    return FixedPoint(sign, value, point)

assert from_float(0.5).to_float() == 0.5
assert from_float(1.5).to_fixed_point(16, 16).value == 98304

def parse(s):
    sign = -1 if s.startswith('-') else 1
    s = s.removeprefix('-')
    integer, fraction = s.split('.')
    assert all(c in string.digits for c in integer), integer
    assert all(c in string.digits for c in fraction), fraction
    assert len(integer) > 0 and len(fraction) > 0, s
    point = 10 ** len(fraction)
    value = int(integer) * point + int(fraction)
    return FixedPoint(
        sign,
        value,
        point
    )

def equal(a, b):
    epsilon = 0.00001
    return (a - b) < epsilon

def assert_raises(e, f):
    try:
        f()
    except e:
        return
    raise AssertionError(f"expected {str(e)}")

assert parse("1.234").value == 1234
assert equal(parse("1.234").to_float(), 1.234)
assert parse("1.234").to_fixed_point(16, 16).value == 80871
assert_raises(FixedPointOverflow,
              lambda: parse("2.234").to_fixed_point(1, 16))
assert parse("2.234").to_fixed_point(2, 16).value == 146407
