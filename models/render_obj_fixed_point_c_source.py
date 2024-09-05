from dataclasses import astuple
import sys
from generate import renderer

from parse_obj_fixed_point import parse_obj_file
from parse_obj_fixed_point import VertexPosition
from parse_obj_fixed_point import VertexNormal
from parse_obj_fixed_point import VertexTexture
from parse_obj_fixed_point import Triangle
from parse_obj_fixed_point import Quadrilateral

from parse_material import parse_mtl_file

vertex_position_fraction_bits = 6 # 4.6
vertex_normal_fraction_bits = 9 # s.9
vertex_texture_fraction_bits = 14 # s.15

def convert_fixed_point(fp, fraction_bits):
    point = 2 ** fraction_bits
    sign = -1 if fp.negative else 1
    n0 = sign * (fp.integer * fp.point + fp.fraction)
    n1 = n0 * point // fp.point
    return n1

def render_index_vtn(index_vtn):
    s = ", ".join(map(str, index_vtn))
    yield f"{{{s}}},"

def render_face(face):
    yield "{"
    for index_vtn in astuple(face):
        yield from render_index_vtn(index_vtn)
    yield "},"

def render_faces(prefix, name, faces):
    yield f"struct {name} {prefix}_{name}[] = {{"
    for face in faces:
        yield from render_face(face)
    yield "};"

def render_triangles(prefix, faces):
    yield from render_faces(prefix, "triangle", faces)

def render_quadrilateral(prefix, faces):
    yield from render_faces(prefix, "quadrilateral", faces)

def xyz(vec):
    return (vec.x, vec.y, vec.z)

def uv(vec):
    return (vec.u, vec.v)

def render_vertex(vertex_tuple, fraction_bits):
    s = ", ".join(
        str(convert_fixed_point(fp, fraction_bits))
        for fp in vertex_tuple
    )
    yield f"{{{s}}},"

def render_vertices(prefix, name, vertices, fraction_bits):
    yield f"// .{fraction_bits} fixed-point"
    yield f"struct vertex_{name} {prefix}_{name}[] = {{"
    for vertex in vertices:
        yield from render_vertex(vertex, fraction_bits)
    yield "};"

def render_vertex_positions(prefix, vertex_positions):
    yield from render_vertices(prefix,
                               "position",
                               map(xyz, vertex_positions),
                               vertex_position_fraction_bits)

def render_vertex_normals(prefix, vertex_normals):
    yield from render_vertices(prefix,
                               "normal",
                               map(xyz, vertex_normals),
                               vertex_normal_fraction_bits)

def render_vertex_texture(prefix, vertex_textures):
    yield from render_vertices(prefix,
                               "texture",
                               map(uv, vertex_textures),
                               vertex_texture_fraction_bits)

def render_object(prefix, object_name, d, material):
    yield f"struct object {prefix}_{object_name} = {{"

    triangle_count = len(d[Triangle]) if Triangle in d else 0
    quadrilateral_count = len(d[Quadrilateral]) if Quadrilateral in d else 0

    if triangle_count > 0:
        yield f".triangle = &{prefix}_{object_name}_triangle[0],"
    else:
        yield f".triangle = NULL,"

    if quadrilateral_count > 0:
        yield f".quadrilateral = &{prefix}_{object_name}_quadrilateral[0],"
    else:
        yield f".quadrilateral = NULL,"

    yield f".triangle_count = {triangle_count},"
    yield f".quadrilateral_count = {quadrilateral_count},"

    if material is None:
        yield f".material = -1,",
    else:
        yield f".material = {material.name},"

    yield "};"

def render_pixel_palette(prefix, newmtl, mapkd):
    name, _ext = mapkd.name.rsplit('.', maxsplit=1)
    pixel_name = f"{name}_data"
    palette_name = f"{name}_data_pal"

    yield f"[{newmtl.name}] = {{"
    yield ".pixel = {"
    yield f".start = (uint8_t *)&_binary_{pixel_name}_start,"
    yield f".end = (uint8_t *)&_binary_{pixel_name}_end,"
    yield f".size = (int)&_binary_{pixel_name}_size,"
    yield "},"
    yield ".palette = {"
    yield f".start = (uint8_t *)&_binary_{palette_name}_start,"
    yield f".end = (uint8_t *)&_binary_{palette_name}_end,"
    yield f".size = (int)&_binary_{palette_name}_size,"
    yield "},"
    yield "},"

def render_materials(prefix, newmtl_mapkd):
    yield f"enum {prefix}_material {{"
    for newmtl, mapkd in newmtl_mapkd:
        yield f"{newmtl.name},";
    yield "};"

    yield f"struct pixel_palette {prefix}_pixel_palette[] = {{"
    for newmtl, mapkd in newmtl_mapkd:
        yield from render_pixel_palette(prefix, newmtl, mapkd)
    yield "};"

def render_header():
    yield '#include "model.h"'
    yield ""

with open(sys.argv[1]) as f:
    buf = f.read()

prefix = sys.argv[2]
vertices, faces, materials = parse_obj_file(buf)
render, out = renderer()
render(render_header())
render(render_vertex_positions(prefix, vertices[VertexPosition]))
render(render_vertex_texture(prefix, vertices[VertexTexture]))
render(render_vertex_normals(prefix, vertices[VertexNormal]))

materials_by_lib_name = set((m.lib, m.name) for m in materials.values())
material_names = set()
for _, name in materials_by_lib_name:
    assert name not in material_names
    material_names.add(name)
material_libs = set(lib for lib, _ in materials_by_lib_name)
for material_lib in material_libs:
    with open(material_lib) as f:
        buf = f.read()
    newmtl_mapkd = [
        (newmtl, mapkd)
        for (newmtl, mapkd) in parse_mtl_file(buf)
        if newmtl.name in material_names
    ]
    render(render_materials(prefix, newmtl_mapkd))

for object_name, d in faces.items():
    object_prefix = '_'.join((prefix, object_name))

    if Triangle in d:
        render(render_triangles(object_prefix, d[Triangle]))
    if Quadrilateral in d:
        render(render_quadrilateral(object_prefix, d[Quadrilateral]))

    render(render_object(prefix, object_name, d, materials.get(object_name)));

sys.stdout.write(out.getvalue())
