OPT = -Os

all: cartridge.bin

phony:

arm9/%.bin: phony
	make -C arm9/ $(notdir $@)

arm7/%.bin: phony
	make -C arm7/ $(notdir $@)

OBJ = \
	header.o \
	arm9/arm9.bin.o \
	arm7/arm7.bin.o
cartridge.elf: $(OBJ)

TRIANGLE_OBJ = \
	header.o \
	arm9/triangle.bin.o \
	arm7/arm7.bin.o
triangle.elf: $(TRIANGLE_OBJ)

TARGET = arm-none-eabi-
AARCH = -march=armv4t -mlittle-endian
OBJARCH = -O elf32-littlearm -B armv4t
LDSCRIPT = cartridge.lds
include common.mk

.PHONY: phony
