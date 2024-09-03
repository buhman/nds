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

triangle.elf: start.o examples/triangle.o

triangle_rotating.elf: start.o examples/triangle_rotating.o ../math/cos_table_fp12.o ../math/cos.o

texture.elf: start.o examples/texture.o ../res/hotaru_futaba.data.o ../res/hotaru_futaba.data.pal.o

CFLAGS += -I../include -I../math

include arm9.mk
include ../common.mk
