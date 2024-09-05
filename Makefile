OPT = -Os

all: cartridge.bin

phony:

arm9/%.bin: phony
	make -C arm9/ $(notdir $@)

arm7/%.bin: phony
	make -C arm7/ $(notdir $@)

DEFAULT = header.o arm7/arm7.bin.o

triangle.elf: $(DEFAULT) arm9/triangle.bin.o
triangle_rotating.elf: $(DEFAULT) arm9/triangle_rotating.bin.o
texture.elf: $(DEFAULT) arm9/texture.bin.o
cube.elf: $(DEFAULT) arm9/cube.bin.o
icosphere.elf: $(DEFAULT) arm9/icosphere.bin.o
majora.elf: $(DEFAULT) arm9/majora.bin.o

TARGET = arm-none-eabi-
AARCH = -march=armv4t -mlittle-endian
OBJARCH = -O elf32-littlearm -B armv4t
LDSCRIPT = cartridge.lds
include common.mk

.PHONY: phony
