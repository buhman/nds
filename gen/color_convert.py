import struct
import sys

from PIL import Image

class color_format:
    def gbgr1555(r, g, b, a): # nintendo ds
        r5 = (r >> 3) & 31
        g6 = (g >> 3) & 31
        g6_l = (g >> 2) & 1
        b5 = (b >> 3) & 31
        return (g6_l << 15) | (b5 << 10) | (g6 << 5) | (r5 << 0)

    def argb4444(r, g, b, a):
        a4 = (a >> 4) & 15
        r4 = (r >> 4) & 15
        g4 = (g >> 4) & 15
        b4 = (b >> 4) & 15
        return (a4 << 12) | (r4 << 8) | (g4 << 4) | (b4 << 0)

    def argb1555(r, g, b, a):
        a1 = (a >> 7) & 1
        r5 = (r >> 3) & 31
        g5 = (g >> 3) & 31
        b5 = (b >> 3) & 31
        return (a1 << 15) | (r5 << 10) | (g5 << 5) | (b5 << 0)

    def rgb565(r, g, b, a):
        r5 = (r >> 3) & 31
        g6 = (g >> 2) & 63
        b5 = (b >> 3) & 31
        return (r5 << 11) | (g5 << 5) | (b5 << 0)

    def from_string(s):
        return dict([
            ("gbgr1555", color_format.gbgr1555),
            ("argb4444", color_format.argb4444),
            ("argb1555", color_format.argb1555),
            ("rgb565", color_format.rgb565),
        ])[s]

in_file = sys.argv[1]
format = sys.argv[2]
out_file = sys.argv[3]

palette = None

with Image.open(in_file) as im:
    width, height = im.size
    if not im.palette:
        pixels = list(im.convert("RGBA").getdata())
    else:
        pixels = list(im.convert("P").getdata())
        palette = list(im.palette.colors)

has_alpha = False
convert = color_format.from_string(format)

def convert_colors(f, colors):
    for color in colors:
        value = convert(*color)
        f.write(struct.pack("<H", value))

if palette is None:
    with open(out_file, 'wb') as f:
        convert_colors(f, pixels)
else:
    with open(out_file, 'wb') as f:
        for pixel in pixels:
            f.write(struct.pack("<B", pixel))
    with open(out_file + '.pal', 'wb') as f:
        convert_colors(f, [(*c, 255) for c in palette])
