from collections import defaultdict
from dataclasses import dataclass
import string

@dataclass
class FixedPoint:
    negative: bool
    integer: int
    fraction: int
    point: int

@dataclass
class VertexPosition:
    x: FixedPoint
    y: FixedPoint
    z: FixedPoint

@dataclass
class VertexNormal:
    x: FixedPoint
    y: FixedPoint
    z: FixedPoint

@dataclass
class VertexTexture:
    u: FixedPoint
    v: FixedPoint

@dataclass
class IndexVTN:
    vertex_position: int
    vertex_texture: int
    vertex_normal: int

@dataclass
class Face:
    a: IndexVTN
    b: IndexVTN
    c: IndexVTN
    d: IndexVTN

def parse_fixed_point(s):
    negative = s.startswith('-')
    s = s.removeprefix('-')
    integer, fraction = s.split('.')
    assert all(c in string.digits for c in integer), integer
    assert all(c in string.digits for c in fraction), fraction
    assert len(integer) > 0 and len(fraction) > 0, s
    return FixedPoint(
        negative,
        int(integer),
        int(fraction),
        10 ** len(fraction)
    )

def parse_fixed_point_vector(args, n):
    split = args.split()
    assert len(split) == n, (n, split)
    return tuple(map(parse_fixed_point, split))

def parse_vertex_position(args):
    coordinates = parse_fixed_point_vector(args, 3)
    yield VertexPosition(*coordinates)

def parse_vertex_normal(args):
    coordinates = parse_fixed_point_vector(args, 3)
    yield VertexNormal(*coordinates)

def parse_vertex_texture(args):
    coordinates = parse_fixed_point_vector(args, 2)
    yield VertexTexture(*coordinates)

def int_minus_one(s):
    n = int(s) - 1
    assert n >= 0
    return n

def parse_vertex_indices(args):
    indices = args.split('/')
    assert len(indices) == 3, indices
    return IndexVTN(*map(int_minus_one, indices))

def parse_face(args):
    vertices = args.split()
    assert len(vertices) == 4, vertices
    yield Face(*map(parse_vertex_indices, vertices))

def parse_obj_line(line):
    prefixes = [
        ('v ', parse_vertex_position),
        ('vn ', parse_vertex_normal),
        ('vt ', parse_vertex_texture),
        ('f ', parse_face)
    ]
    for prefix, parser in prefixes:
        if line.startswith(prefix):
            args = line.removeprefix(prefix)
            yield from parser(args)

def group_by_type(l):
    grouped = defaultdict(list)
    for i in l:
        grouped[type(i)].append(i)
    return dict(grouped)

def parse_obj_file(buf):
    return group_by_type((
        parsed
        for line in buf.strip().split('\n')
        for parsed in parse_obj_line(line)
        if not line.startswith('#')
    ))
