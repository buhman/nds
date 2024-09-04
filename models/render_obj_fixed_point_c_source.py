from dataclasses import astuple
import sys
from generate import renderer

from parse_obj_fixed_point import parse_obj_file
from parse_obj_fixed_point import VertexPosition
from parse_obj_fixed_point import VertexNormal
from parse_obj_fixed_point import VertexTexture
from parse_obj_fixed_point import Face

vertex_position_fraction_bits = 6 # 4.6
vertex_normal_fraction_bits = 9 # s.9
vertex_texture_fraction_bits = 15 # s.15

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

def render_faces(prefix, faces):
    yield f"struct face {prefix}_faces[] = {{"
    for face in faces:
        yield from render_face(face)
    yield "};"

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
    yield f"struct vertex_{name} {prefix}_{name}s[] = {{"
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

def render_header():
    yield '#include "model.h"'
    yield ""

with open(sys.argv[1]) as f:
    buf = f.read()

prefix = sys.argv[2]
d = parse_obj_file(buf)
render, out = renderer()
render(render_header())
render(render_vertex_positions(prefix, d[VertexPosition]))
render(render_vertex_texture(prefix, d[VertexTexture]))
render(render_vertex_normals(prefix, d[VertexNormal]))
render(render_faces(prefix, d[Face]))
sys.stdout.write(out.getvalue())
