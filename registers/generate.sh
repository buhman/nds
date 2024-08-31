python format.py 0x04000000.txt graphics_engine_a > graphics_engine_a.h
python format.py 0x04001000.txt graphics_engine_b > graphics_engine_b.h

make graphics_engine_bits.csv
python format_bits.py graphics_engine_bits.csv > graphics_engine_bits.h
