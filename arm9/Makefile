OPT = -Og

ALL = \
	arm9.bin \
	triangle.bin

all: arm9.bin

2D_ENGINE_OBJ = \
	start.o \
	2d_engine.o \
	../texture/player.data.o \
	../texture/player.data.pal.o \
	../texture/bowser.data.o \
	../texture/bowser.data.pal.o

include ../texture/texture.mk

2d_engine.elf: $(2D_ENGINE_OBJ)

triangle.elf: start.o examples/triangle.o

triangle_rotating.elf: start.o examples/triangle_rotating.o ../math/cos_table_fp12.o ../math/cos.o

texture.elf: start.o examples/texture.o ../res/hotaru_futaba.data.o ../res/hotaru_futaba.data.pal.o

cube.elf: start.o examples/cube.o ../math/cos_table_fp12.o ../math/cos.o

icosphere.elf: start.o examples/icosphere.o ../math/cos_table_fp12.o ../math/cos.o

MAJORA_RES = \
	../texture/060067E0.data.pal.o \
	../texture/060079E0.data.pal.o \
	../texture/06007DE0.data.pal.o \
	../texture/060077E0.data.pal.o \
	../texture/06007BE0.data.pal.o \
	../texture/06007FE0.data.pal.o \
	../texture/060067E0.data.o \
	../texture/060079E0.data.o \
	../texture/06007DE0.data.o \
	../texture/060077E0.data.o \
	../texture/06007BE0.data.o \
	../texture/06007FE0.data.o

examples/majora.c: $(patsubst %.o,%.h,$(MAJORA_RES))

majora.elf: start.o examples/majora.o ../math/cos_table_fp12.o ../math/cos.o $(MAJORA_RES)

CFLAGS += -I../include -I../

include arm9.mk
include ../common.mk
