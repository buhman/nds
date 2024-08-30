def crc16_modbus(b: bytes) -> int:
    crc = 0xFFFF
    for n in range(len(b)):
        crc ^= b[n]
        for i in range(8):
            if crc & 1:
                crc >>= 1
                crc ^= 0xA001
            else:
                crc >>= 1
    return crc

logo = [
    0x24, 0xff, 0xae, 0x51, 0x69, 0x9a, 0xa2, 0x21,
    0x3d, 0x84, 0x82, 0x0a, 0x84, 0xe4, 0x09, 0xad,
    0x11, 0x24, 0x8b, 0x98, 0xc0, 0x81, 0x7f, 0x21,
    0xa3, 0x52, 0xbe, 0x19, 0x93, 0x09, 0xce, 0x20,
    0x10, 0x46, 0x4a, 0x4a, 0xf8, 0x27, 0x31, 0xec,
    0x58, 0xc7, 0xe8, 0x33, 0x82, 0xe3, 0xce, 0xbf,
    0x85, 0xf4, 0xdf, 0x94, 0xce, 0x4b, 0x09, 0xc1,
    0x94, 0x56, 0x8a, 0xc0, 0x13, 0x72, 0xa7, 0xfc,
    0x9f, 0x84, 0x4d, 0x73, 0xa3, 0xca, 0x9a, 0x61,
    0x58, 0x97, 0xa3, 0x27, 0xfc, 0x03, 0x98, 0x76,
    0x23, 0x1d, 0xc7, 0x61, 0x03, 0x04, 0xae, 0x56,
    0xbf, 0x38, 0x84, 0x00, 0x40, 0xa7, 0x0e, 0xfd,
    0xff, 0x52, 0xfe, 0x03, 0x6f, 0x95, 0x30, 0xf1,
    0x97, 0xfb, 0xc0, 0x85, 0x60, 0xd6, 0x80, 0x25,
    0xa9, 0x63, 0xbe, 0x03, 0x01, 0x4e, 0x38, 0xe2,
    0xf9, 0xa2, 0x34, 0xff, 0xbb, 0x3e, 0x03, 0x44,
    0x78, 0x00, 0x90, 0xcb, 0x88, 0x11, 0x3a, 0x94,
    0x65, 0xc0, 0x7c, 0x63, 0x87, 0xf0, 0x3c, 0xaf,
    0xd6, 0x25, 0xe4, 0x8b, 0x38, 0x0a, 0xac, 0x72,
    0x21, 0xd4, 0xf8, 0x07,
]
logo_b = bytes(logo)
assert crc16_modbus(logo_b) == 0xcf56

import sys
with open(sys.argv[1], 'rb') as f:
    buf = bytearray(f.read())

assert buf[0x15c] == 0x56
assert buf[0x15d] == 0xcf

logo_crc = crc16_modbus(buf[0x0c0:0xc0 + 0x9c])
print(hex(logo_crc))
assert logo_crc == 0xcf56

header_crc = crc16_modbus(buf[0:0x15e])
print(hex(header_crc))

import struct
header_crc_b = struct.pack('<H', header_crc)

buf[0x15e] = header_crc_b[0]
buf[0x15f] = header_crc_b[1]

with open(sys.argv[2], 'wb') as f:
    f.write(buf)