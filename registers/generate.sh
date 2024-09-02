set -eux

python format.py 0x04000000.txt graphics_engine_a 0x1000 > ../include/graphics_engine_a.h
python format.py 0x04001000.txt graphics_engine_b 0 > ../include/graphics_engine_b.h

make graphics_engine_bits.csv
python format_bits.py graphics_engine_bits.csv > ../include/bits.h
