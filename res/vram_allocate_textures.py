from dataclasses import dataclass
from generate import renderer
from math import log
from path import texture_path
import sys

from PIL import Image

from parse_material import parse_mtl_file

material_filenames = sys.argv[1:]

def render_material_enum(newmtl_mapkd):
    yield f"enum material {{"
    for newmtl, mapkd in newmtl_mapkd:
        yield f"{newmtl.name},";
    yield "};"

def render_pixel_descriptor(offset, mapkd, dimensions):
    name, _ext = mapkd.name.rsplit('.', maxsplit=1)
    pixel_name = f"{name}_data"
    width, height = dimensions
    yield ".pixel = {"
    yield f".start = (uint8_t *)&_binary_{pixel_name}_start,"
    yield f".size = (int)&_binary_{pixel_name}_size,"
    yield f".vram_offset = {offset.pixel},"
    yield f".width = {width},"
    yield f".height = {height},"
    yield "},"

def render_palette_descriptor(offset, mapkd, palette_size):
    name, _ext = mapkd.name.rsplit('.', maxsplit=1)
    palette_name = f"{name}_data_pal"
    yield ".palette = {"
    yield f".start = (uint8_t *)&_binary_{palette_name}_start,"
    yield f".size = (int)&_binary_{palette_name}_size,"
    yield f".vram_offset = {offset.palette},"
    yield f".palette_size = {palette_size},"
    yield "},"

@dataclass
class Offset:
    pixel: int
    palette: int

def round_up_colors(name, colors):
    assert colors != 0, (name, colors)
    if colors <= 4:
        return 4
    elif colors <= 16:
        return 16
    elif colors <= 256:
        return 256
    else:
        assert False, (name, colors)

def image_metadata(mapkd):
    path = texture_path(mapkd.name)
    with Image.open(path) as im:
        dimensions = im.size
        colors = len(im.palette.colors)
    return dimensions, colors

def round_up_n(x, multiple):
    return ((x + multiple - 1) // multiple) * multiple

def bytes_per_pixel(palette_size):
    bits_per_pixel = int(log(palette_size)/log(2))
    return bits_per_pixel / 8

def render_material(offset, mapkd):
    dimensions, colors = image_metadata(mapkd)
    palette_size = round_up_colors(mapkd.name, colors)

    # pixel descriptor
    yield from render_pixel_descriptor(offset, mapkd, dimensions)
    pixel_size = bytes_per_pixel(palette_size) * dimensions[0] * dimensions[1]
    assert int(pixel_size) == pixel_size
    offset.pixel += round_up_n(int(pixel_size), 8)

    # palette descriptor
    yield from render_palette_descriptor(offset, mapkd, palette_size)
    offset.palette += round_up_n(colors * 2, 16)

def render_materials(newmtl_mapkd):
    yield "struct material_descriptor material[] = {"
    offset = Offset(0, 0)
    for newmtl, mapkd in newmtl_mapkd:
        yield f"[{newmtl.name}] = {{"
        yield from render_material(offset, mapkd)
        yield "},"
    yield "};"

def render_header():
    yield "#pragma once"
    yield ""
    yield "#include <stdint.h>"
    yield ""
    yield '#include "model/material.h"'
    yield ""

if __name__ == "__main__":
    material_filenames = sys.argv[1:]
    newmtl_mapkd = []
    for material_filename in material_filenames:
        with open(material_filename) as f:
            buf = f.read()
            newmtl_mapkd.extend([
                (newmtl, mapkd)
                for (newmtl, mapkd) in parse_mtl_file(buf)
            ])

    render, out = renderer()
    render(render_header())
    render(render_material_enum(newmtl_mapkd))
    render(render_materials(newmtl_mapkd))
    sys.stdout.write(out.getvalue())
