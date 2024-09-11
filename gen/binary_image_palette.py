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

def pack_one_byte(pixels, index, colors, palette_size):
    color_count = len(colors)
    num = pixels_per_byte(palette_size)
    shift = 8 // num
    byte = 0
    i = 0
    while num > 0:
        px, alpha = pixels[index]
        if alpha == 0 and color_count < palette_size:
            px = color_count
        assert px < palette_size
        byte |= px << (shift * i)
        index += 1
        i += 1
        num -= 1
    return [byte], index

def pack_one_texel(pixels, index, colors, palette_size):
    px, alpha = pixels[index]
    return

def pack_pixels(pixels, width, height, colors, palette_size):
    index = 0
    with open(sys.argv[2], 'wb') as f:
        while index < (width * height):
            byte_list, index = pack_texel(pixels, index, colors, palette_size)
            f.write(bytes(byte))

def pack_palette(colors, palette_size):
    with open(sys.argv[2], 'wb') as f:
        for color in colors:
            out = argb1555(255, *color)
            f.write(struct.pack('<H', out))
        if len(colors) < palette_size:
            # transparent color
            print('pack transparency at ix', len(colors))
            out = argb1555(0, 0, 0, 0)
            f.write(struct.pack('<H', out))

with Image.open(sys.argv[1]) as im:
    assert im.mode == "P"
    width, height = im.size
    colors = list(im.palette.colors)
    pixels = list(im.convert("PA").getdata())

palette_size = round_up_palette_size(len(colors))
if sys.argv[2].endswith('.data'):
    pack_pixels(pixels, width, height, len(colors), palette_size)
elif sys.argv[2].endswith('.pal'):
    pack_palette(colors, palette_size)
else:
    assert False, sys.argv[2]
