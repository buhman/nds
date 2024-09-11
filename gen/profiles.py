from dataclasses import dataclass

@dataclass
class Profile:
    position: tuple[int, int]
    texture: tuple[int, int]
    normal: tuple[int, int]

@dataclass
class FixedPointBits:
    integer: int
    fraction: int

    def to_str(self):
        return f"{self.integer}.{self.fraction} fixed-point"

@dataclass
class FloatingPoint:
    def to_str(self):
        return f"floating-point"

profiles = {}

profiles["nds"] = Profile(
    position = FixedPointBits(4, 6),  # 4.6
    normal   = FixedPointBits(0, 9),  # 0.9
    texture  = FixedPointBits(1, 14), # 1.14
)

profiles["dreamcast"] = Profile(
    position = FloatingPoint(),
    normal = FloatingPoint(),
    texture = FloatingPoint(),
)
