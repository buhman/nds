from dataclasses import astuple
import sys
from generate import renderer

from parse_obj import parse_obj_file
from parse_obj import VertexPosition
from parse_obj import VertexNormal
from parse_obj import VertexTexture
from parse_obj import Triangle
from parse_obj import Quadrilateral

import profiles

def render_index_vtn(index_vtn):
    s = ", ".join(map(str, index_vtn))
    yield f"{{{s}}},"

def render_face(face):
    yield "{ .v = {"
    for index_vtn in astuple(face):
        yield from render_index_vtn(index_vtn)
    yield "}},"

def render_faces(prefix, name, faces):
    yield f"union {name} {prefix}_{name}[] = {{"
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

def render_vertex(profile_item, vertex_tuple):
    def _profile_item(profile_item, fp):
        if type(profile_item) == profiles.FixedPointBits:
            return fp.to_fixed_point(profile_item.integer, profile_item.fraction).to_int()
        elif type(profile_item) == profiles.FloatingPoint:
            return fp.to_float()
        else:
            assert False, type(profile_item)

    s = ", ".join(
        str(_profile_item(profile_item, fp))
        for fp in vertex_tuple
    )
    yield f"{{{s}}},"

def render_vertices(profile_item, prefix, name, vertices):
    yield f"// {profile_item.to_str()}"
    yield f"vertex_{name} {prefix}_{name}[] = {{"
    for vertex in vertices:
        yield from render_vertex(profile_item, vertex)
    yield "};"

def render_vertex_positions(profile, prefix, vertex_positions):
    yield from render_vertices(profile.position,
                               prefix,
                               "position",
                               map(xyz, vertex_positions))

def render_vertex_normals(profile, prefix, vertex_normals):
    yield from render_vertices(profile.normal,
                               prefix,
                               "normal",
                               map(xyz, vertex_normals))

def render_vertex_texture(profile, prefix, vertex_textures):
    yield from render_vertices(profile.texture,
                               prefix,
                               "texture",
                               map(uv, vertex_textures))

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

def render_object_list(prefix, object_names):
    yield f"struct object * {prefix}_object_list[] = {{"
    for object_name in object_names:
        yield f"&{prefix}_{object_name},"
    yield "};"

def render_model(prefix, object_count):
    yield f"struct model {prefix}_model = {{"
    yield f".position = &{prefix}_position[0],"
    yield f".texture = &{prefix}_texture[0],"
    yield f".normal = &{prefix}_normal[0],"
    yield f".object = &{prefix}_object_list[0],"
    yield f".object_count = {object_count},"
    yield "};"

def render_header():
    yield "#pragma once"
    yield ""
    yield "#include <stddef.h>"
    yield ""
    yield '#include "../model.h"'
    yield ""

obj_filename = sys.argv[1]
prefix = sys.argv[2]
profile_name = sys.argv[3]

profile = profiles.profiles[profile_name]

with open(obj_filename) as f:
    buf = f.read()

vertices, faces, materials = parse_obj_file(buf)
render, out = renderer()
render(render_header())
render(render_vertex_positions(profile, prefix, vertices[VertexPosition]))
render(render_vertex_texture(profile, prefix, vertices[VertexTexture]))
render(render_vertex_normals(profile, prefix, vertices[VertexNormal]))

for object_name, d in faces.items():
    object_prefix = '_'.join((prefix, object_name))

    if Triangle in d:
        render(render_triangles(object_prefix, d[Triangle]))
    if Quadrilateral in d:
        render(render_quadrilateral(object_prefix, d[Quadrilateral]))

    render(render_object(prefix, object_name, d, materials.get(object_name)));

render(render_object_list(prefix, faces.keys()))
render(render_model(prefix, len(faces)))

sys.stdout.write(out.getvalue())
