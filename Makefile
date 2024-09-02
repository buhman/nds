OPT = -Os

OBJ = \
	header.o \
	arm9/arm9.bin.o \
	arm7/arm7.bin.o

all: cartridge.bin

cartridge.elf: $(OBJ)

TARGET = arm-none-eabi-
AARCH = -march=armv4t -mlittle-endian
OBJARCH = -O elf32-littlearm -B armv4t
LDSCRIPT = cartridge.lds
include common.mk
