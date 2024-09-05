import sys

from parse_obj_fixed_point import parse_obj_file
from parse_obj_fixed_point import VertexPosition
from parse_obj_fixed_point import VertexNormal
from parse_obj_fixed_point import VertexTexture
from parse_obj_fixed_point import Triangle

def convert_fixed_point(fp, fraction_bits):
    point = 2 ** fraction_bits
    sign = -1 if fp.negative else 1
    n0 = sign * (fp.integer * fp.point + fp.fraction)
    n1 = n0 * point // fp.point
    return n1

from pprint import pprint

with open(sys.argv[1]) as f:
    buf = f.read()

vertices, faces, materials = parse_obj_file(buf)

position = vertices[VertexPosition]
texture = vertices[VertexTexture]
normal = vertices[VertexNormal]

def flt(fp):
    sign = -1 if fp.negative else 1
    return sign * (fp.integer + fp.fraction / fp.point)

for object_name, d in faces.items():
    if object_name != '3':
        continue
    triangle = d[Triangle]
    for t in triangle:
        at = texture[t.a.vertex_texture]
        bt = texture[t.b.vertex_texture]
        ct = texture[t.c.vertex_texture]
        print((flt(at.u), flt(at.v)),
              (flt(bt.u), flt(bt.v)),
              (flt(ct.u), flt(ct.v)))

        verts = [at, bt, ct]

        pprint([
            (convert_fixed_point(t.u, 15), convert_fixed_point(t.v, 15)) for t in verts
        ])

        pprint([
            [((convert_fixed_point(c, 15) * 31) >> 11) // (2 ** 4) for c in [t.u, t.v]] for t in verts
        ])
