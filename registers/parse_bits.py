from collections import defaultdict
from dataclasses import dataclass
from typing import Union

def aggregate_registers(d):
    aggregated = defaultdict(list)
    for row in d:
        #assert row["register_name"] != ""
        aggregated[row["register_name"]].append(row)
    return dict(aggregated)

def parse_bit_number(s):
    assert '-' not in s
    return int(s, 10)

def parse_bit_set(s, split_char):
    assert len(list(c for c in s if c == split_char)) == 1
    left, right = map(parse_bit_number, s.split(split_char, maxsplit=1))
    assert left > right, (left, right)
    return left, right

def parse_bit_range(s):
    if '-' in s:
        left, right = parse_bit_set(s, '-')
        return set(range(right, left+1))
    elif ',' in s:
        left, right = parse_bit_set(s, ',')
        return set([right, left])
    else:
        num = parse_bit_number(s)
        return set([num])

def parse_bit_range(s):
    if '-' in s:
        left, right = parse_bit_set(s, '-')
        return set(range(right, left+1))
    elif ',' in s:
        left, right = parse_bit_set(s, ',')
        return set([right, left])
    else:
        num = parse_bit_number(s)
        return set([num])

def parse_value(value):
    return eval(value)

@dataclass
class Bit:
    name: str
    bits: set[int]
    mask: Union[None, int]
    value: Union[None, int]

@dataclass
class Enum:
    name: str
    defs: list[dict]

@dataclass
class Register:
    block: Union[None, str]
    name: str
    defs: list[Union[dict, Enum]]

def parse_row(row):
    return Bit(
        name=row['bit_name'],
        bits=parse_bit_range(row['bits']),
        mask=parse_value(row['mask']) if row['mask'].strip() else None,
        value=parse_value(row['value']) if row['value'].strip() else None,
    )

def aggregate_enums(aggregated_rows):
    non_enum = []
    enum_aggregated = defaultdict(list)
    all_bits = set()
    enum_bits = dict()
    non_enum_bits = list()

    def assert_unique_ordered(bits, row):
        nonlocal all_bits
        assert all(bit not in all_bits for bit in bits), (bits, row)
        assert max(all_bits, default=32) > max(bits), (all_bits, bits)
        all_bits |= bits

    def enum_bits_name(row):
        return (row["register_name"], row["enum_name"])

    for row in aggregated_rows:
        bit = parse_row(row)
        assert row["bit_name"] != "", row
        if row["enum_name"] == "":
            if bit.bits not in non_enum_bits:
                assert_unique_ordered(bit.bits, row)
            non_enum.append(bit)
            non_enum_bits.append(bit.bits)
        else:
            if enum_bits_name(row) not in enum_bits:
                if bit.bits not in enum_bits.values():
                    #assert_unique_ordered(bit.bits, row)
                    pass
                non_enum.append(row["enum_name"])
            else:
                eb = enum_bits[enum_bits_name(row)]
                assert eb == bit.bits or (eb & bit.bits) == set(), row

            enum_bits[enum_bits_name(row)] = bit.bits
            enum_aggregated[row["enum_name"]].append(bit)

    return non_enum, dict(enum_aggregated)

def aggregate_all_enums(aggregated):
    out = []
    for register_name, rows in aggregated.items():
        non_enum, enum_aggregated = aggregate_enums(rows)
        def resolve(row_or_string):
            if type(row_or_string) == str:
                return Enum(row_or_string,
                            enum_aggregated[row_or_string])
            elif type(row_or_string) == Bit:
                return row_or_string
            else:
                assert False, (row_or_string, type(row_or_string))

        defs = [resolve(aggregate) for aggregate in non_enum]
        if 'block' in rows[0]:
            blocks = set(row['block'] for row in rows)
            assert len(blocks) == 1, blocks
            block_name = next(iter(blocks))
            out.append(
                Register(block_name, register_name, defs))
        else:
            out.append(
                Register(None, register_name, defs))
    return out
