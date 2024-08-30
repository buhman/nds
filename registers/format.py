import sys
from parse import register_descriptions

struct_name = sys.argv[2]

with open(sys.argv[1]) as f:
    buf = f.read()
    lines = buf.strip().split('\n')

registers = register_descriptions(lines)

def type_by_size(size):
    if size == 2:
        return 'volatile uint16_t'
    elif size == 4:
        return 'volatile uint32_t'
    elif size == 8:
        return 'volatile uint64_t'
    else:
        assert False, size

def c_source(registers):
    struct_offset = 0
    pad_ix = 0

    for register in registers:
        assert register.offset >= struct_offset, register
        if register.offset != struct_offset:
            pad_size = register.offset - struct_offset
            yield f"volatile uint8_t _pad{pad_ix}[{pad_size}];"
            pad_ix += 1
            struct_offset += pad_size

        type = type_by_size(register.size)
        yield f"{type} {register.name};"

        struct_offset += register.size

def c_asserts(registers):
    for register in registers:
        yield f"static_assert((offsetof (struct {struct_name}, {register.name})) == 0x{register.offset:03x});"

print('#include <stdint.h>')
print('#include <stddef.h>')
print('#include <assert.h>')
print('')
print(f'struct {struct_name} {{')
for line in c_source(registers):
    print('  ' + line)
print('};')
for line in c_asserts(registers):
    print(line)
print()
print(f'extern struct {struct_name} {struct_name} __asm("{struct_name}");')
