from dataclasses import dataclass

@dataclass
class Register:
    offset: int
    size: int
    name: str
    page: int
    description: str

def parse_fields(line):
    fields = line.split(' ', maxsplit=3)
    assert len(fields) in {1, 4}, fields
    if len(fields) == 1:
        offset, = fields
        return [int(offset, 16)]
    else:
        offset, name, page, description = fields
        return [int(offset, 16), name, int(page, 10), description]

def register_descriptions(lines):
    last_offset = -2
    result = []

    for line in lines:
        if not line.strip():
            continue

        fields = parse_fields(line)
        if len(fields) == 1:
            offset, = fields
            assert last_offset + 2 == offset, (last_offset, line)
            result[len(result) - 1].size += 2
            last_offset = offset
        else:
            offset, name, page, description = fields
            result.append(Register(
                offset,
                2, # size
                name.upper(),
                page,
                description,
            ))
            last_offset = offset

    return result
