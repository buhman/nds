import struct
import sys

fields = [
    ("game title", 0x000, 0xc),
    ("game code",  0x00c, 0x4),
    ("maker code", 0x010, 0x2),
    ("main unit code", 0x012, 0x1),
    ("device type", 0x013, 0x1),
    ("device capacity", 0x014, 0x1),
    ("reserved 015", 0x015, 0x8),
    ("specific", 0x01d, 0x1),
    ("rom version", 0x01e, 0x1),
    ("reserved 01f", 0x01f, 0x1),
    ("arm9 resident module rom offset", 0x020, 0x4),
    ("arm9 resident module entry address", 0x024, 0x4),
    ("arm9 resident module ram address", 0x028, 0x4),
    ("arm9 resident module rom size", 0x02c, 0x4),
    ("arm7 resident module rom offset", 0x030, 0x4),
    ("arm7 resident module entry address", 0x034, 0x4),
    ("arm7 resident module ram address", 0x038, 0x4),
    ("arm7 resident module rom size", 0x03c, 0x4),
    ("file name table rom offset", 0x040, 0x4),
    ("file name table rom size", 0x044, 0x4),
    ("file allocation table rom offset", 0x048, 0x4),
    ("file allocation table rom size", 0x04c, 0x4),
    ("arm9 overlay table rom offset", 0x050, 0x4),
    ("arm9 overlay table rom size", 0x054, 0x4),
    ("arm7 overlay table rom offset", 0x058, 0x4),
    ("arm7 overlay table rom size", 0x05c, 0x4),
    ("rom control information 060", 0x060, 0x4),
    ("rom control information 064", 0x064, 0x4),
    ("banner file rom offset", 0x068, 0x4),
    ("secure area crc", 0x06c, 0x2),
    ("rom control information 06e", 0x06e, 0x2),
    ("arm9 auto load list ram address", 0x070, 0x4),
    ("arm7 auto load list ram address", 0x074, 0x4),
    ("rom information reserved region", 0x078, 0x8),
    ("application", 0x080, 0x4),
    ("rom header size", 0x084, 0x4),
    ("arm9 module parameter address", 0x088, 0x4),
    ("arm7 module parameter address", 0x08c, 0x4),
]

with open(sys.argv[1], 'rb') as f:
    buf = f.read()

file_offset = 0

for name, offset, size in fields:
    assert offset == file_offset, (hex(offset), hex(file_offset))
    file_offset += size
    pad = ' ' * (35 - len(name))
    print(f"{name}: {pad}", end='')
    if size < 16:
        for i in range(size):
            b = buf[offset + i]
            print(f'{b:02x}', end='')

    pad = ' ' * (17 * 2 - size * 2)
    if size == 4:
        n, = struct.unpack('<I', buf[offset:offset+size])
        print(pad, f"0x{n:08x}", end='')
    if size == 2:
        n, = struct.unpack('<H', buf[offset:offset+size])
        print(pad, f"0x{n:04x}", end='')
    print()
