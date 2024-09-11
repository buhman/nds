from dataclasses import dataclass

@dataclass
class NewMtl:
    name: str

@dataclass
class MapKd:
    name: str

def parse_material_newmtl(args):
    name, = args.split()
    yield NewMtl(name.replace('-', '_').replace('.', '_'))

def parse_material_mapkd(args):
    name, = args.split()
    yield MapKd(name)

def parse_mtl_line(line):
    prefixes = [
        ('newmtl ', parse_material_newmtl),
        ('map_Kd ', parse_material_mapkd),
    ]
    for prefix, parser in prefixes:
        if line.startswith(prefix):
            args = line.removeprefix(prefix)
            yield from parser(args)

def group_by_material(l):
    current_material = None
    for i in l:
        if type(i) is NewMtl:
            current_material = i
        elif type(i) is MapKd:
            assert current_material is not None
            yield (current_material, i)
            current_material = None
        else:
            assert False, type(i)

def parse_mtl_file(buf):
    return list(group_by_material((
        parsed
        for line in buf.strip().split('\n')
        for parsed in parse_mtl_line(line)
        if not line.startswith('#')
    )))
