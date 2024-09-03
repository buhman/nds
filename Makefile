OPT = -Os

OBJ = \
	header.o \
	arm9/arm9.bin.o \
	arm7/arm7.bin.o

all: cartridge.bin

arm9/arm9.bin:
	make -C arm9/

arm7/arm7.bin:
	make -C arm7/

cartridge.elf: $(OBJ)

TARGET = arm-none-eabi-
AARCH = -march=armv4t -mlittle-endian
OBJARCH = -O elf32-littlearm -B armv4t
LDSCRIPT = cartridge.lds
include common.mk

.PHONY: arm9/arm9.bin arm7/arm7.bin
