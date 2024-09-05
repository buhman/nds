OPT = -Og

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

cube.elf: start.o examples/cube.o ../math/cos_table_fp12.o ../math/cos.o

icosphere.elf: start.o examples/icosphere.o ../math/cos_table_fp12.o ../math/cos.o

MAJORA_RES = \
	../res/060067E0.data.pal.o \
	../res/060079E0.data.pal.o \
	../res/06007DE0.data.pal.o \
	../res/060077E0.data.pal.o \
	../res/06007BE0.data.pal.o \
	../res/06007FE0.data.pal.o \
	../res/060067E0.data.o \
	../res/060079E0.data.o \
	../res/06007DE0.data.o \
	../res/060077E0.data.o \
	../res/06007BE0.data.o \
	../res/06007FE0.data.o

majora.elf: start.o examples/majora.o ../math/cos_table_fp12.o ../math/cos.o $(MAJORA_RES)

CFLAGS += -I../include -I../

include arm9.mk
include ../common.mk
