import sys

from csv_input import read_input

from parse_bits import aggregate_registers
from parse_bits import aggregate_all_enums
from parse_bits import Enum, Bit
from generate import renderer

def mask_from_bits(bits):
    h, l = max(bits), min(bits)
    mask = 2 ** ((h - l) + 1) - 1
    return mask

def render_bit(prefix, bit):
    macro_name = f"{prefix}__{bit.name}"
    if bit.value is None and bit.mask is None:
        # value read macro
        mask_value = mask_from_bits(bit.bits)
        yield f"#define {macro_name}(v) (((v) >> {min(bit.bits)}) & {hex(mask_value)})"
    elif bit.mask is None:
        # constant value macro
        yield f"#define {macro_name} ({hex(bit.value)} << {min(bit.bits)})"
    elif bit.value is None:
        # variable macro
        mask_value = mask_from_bits(bit.bits)
        assert bit.mask & mask_value == mask_value, (bit.mask, mask_value)
        yield f"#define {macro_name}(v) (((v) & {hex(mask_value)}) << {min(bit.bits)})"
    else:
        assert False, bit

def render_enum(prefix, enum):
    enum_prefix = f"{prefix}__{enum.name}"
    for bit in enum.defs:
        yield from render_bit(enum_prefix, bit)

def render_register(register):
    for bit_or_enum in register.defs:
        if type(bit_or_enum) is Enum:
            yield from render_enum(register.name, bit_or_enum)
        elif type(bit_or_enum) is Bit:
            yield from render_bit(register.name, bit_or_enum)
        else:
            assert False, (bit_or_enum, type(bit_or_enum))

def render_registers(registers):
    for register in registers:
        yield from render_register(register)

if __name__ == "__main__":
    d = read_input(sys.argv[1])
    aggregated = aggregate_registers(d)
    registers = aggregate_all_enums(aggregated)
    render, out = renderer()
    render(render_registers(registers))
    sys.stdout.write(out.getvalue())
