OPT = -Os

ALL = \
	arm9.bin \
	triangle.bin

all: arm9.bin

OBJ = \
	start.o \
	main.o \
	../res/player.data.o \
	../res/player.data.pal.o \
	../res/bowser.data.o \
	../res/bowser.data.pal.o

arm9.elf: $(OBJ)

foo = start.o examples/triangle.o
triangle.elf: $(foo)

CFLAGS += -I../include

include arm9.mk
include ../common.mk
