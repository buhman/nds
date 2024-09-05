import struct
import sys

from PIL import Image

def round_up_palette_size(palette_size):
    assert palette_size != 0, (name, palette_size)
    if palette_size <= 4:
        return 4
    elif palette_size <= 16:
        return 16
    elif palette_size <= 256:
        return 256
    else:
        assert False, palette_size

def pixels_per_byte(palette_size):
    if palette_size == 4:
        return 4
    elif palette_size == 16:
        return 2
    elif palette_size == 256:
        return 1
    else:
        assert False, palette_size

def pack_one_byte(pixels, index, palette_size):
    num = pixels_per_byte(palette_size)
    shift = 8 // num
    byte = 0
    i = 0
    while num > 0:
        px = pixels[index]
        assert px < palette_size
        byte |= px << (shift * i)
        index += 1
        i += 1
        num -= 1
    return byte, index

def pack_pixels(pixels, width, height, palette_size):
    index = 0
    with open(sys.argv[2], 'wb') as f:
        while index < (width * height):
            byte, index = pack_one_byte(pixels, index, palette_size)
            f.write(bytes([byte]))

def rgb565(r, g, b):
    r5 = (r >> 3) & 31
    g6 = (g >> 3) & 31
    g6_l = (g >> 2) & 1
    b5 = (b >> 3) & 31
    return (g6_l << 15) | (b5 << 10) | (g6 << 5) | (r5 << 0)

def pack_palette(colors):
    with open(sys.argv[2], 'wb') as f:
        for color in colors:
            out = rgb565(*color)
            f.write(struct.pack('<H', out))

with Image.open(sys.argv[1]) as im:
    width, height = im.size
    colors = list(im.palette.colors)
    pixels = list(im.getdata())

if sys.argv[2].endswith('.data'):
    pack_pixels(pixels, width, height, round_up_palette_size(len(colors)))
elif sys.argv[2].endswith('.pal'):
    pack_palette(colors)
else:
    assert False, sys.argv[2]
