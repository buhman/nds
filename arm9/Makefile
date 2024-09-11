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

ULALA_RES = \
	../model/ulala/eye.data.o \
	../model/ulala/ha.data.o \
	../model/ulala/p03b_hair.data.o \
	../model/ulala/p_face.data.o \
	../model/ulala/p_nomal_mix.data.o \
	../model/ulala/p_ref_or.data.o \
	../model/ulala/u_lb.data.o \
	../model/ulala/eye.data.pal.o \
	../model/ulala/ha.data.pal.o \
	../model/ulala/p03b_hair.data.pal.o \
	../model/ulala/p_face.data.pal.o \
	../model/ulala/p_nomal_mix.data.pal.o \
	../model/ulala/p_ref_or.data.pal.o \
	../model/ulala/u_lb.data.pal.o

examples/ulala.c: $(patsubst %.o,%.h,$(ULALA_RES))
ulala.elf: start.o examples/ulala.o ../math/cos_table_fp12.o ../math/cos.o $(ULALA_RES)


HAPPY_MASK_SALESMAN_RES = \
	../model/happy_mask_salesman/mask_00_8A00.data.o \
	../model/happy_mask_salesman/mask_01_9200.data.o \
	../model/happy_mask_salesman/mask_02_9A00.data.o \
	../model/happy_mask_salesman/mask_03_A200.data.o \
	../model/happy_mask_salesman/mask_04_AA00.data.o \
	../model/happy_mask_salesman/mask_05_B200.data.o \
	../model/happy_mask_salesman/mask_06_BA00.data.o \
	../model/happy_mask_salesman/mask_07_C200.data.o \
	../model/happy_mask_salesman/mask_08_CA00.data.o \
	../model/happy_mask_salesman/mask_09_D200.data.o \
	../model/happy_mask_salesman/maskmaster_00_0.data.o \
	../model/happy_mask_salesman/maskmaster_01_4A00.data.o \
	../model/happy_mask_salesman/maskmaster_e00_6A00.data.o \
	../model/happy_mask_salesman/maskmaster_m00_7A00.data.o \
	../model/happy_mask_salesman/mask_00_8A00.data.pal.o \
	../model/happy_mask_salesman/mask_01_9200.data.pal.o \
	../model/happy_mask_salesman/mask_02_9A00.data.pal.o \
	../model/happy_mask_salesman/mask_03_A200.data.pal.o \
	../model/happy_mask_salesman/mask_04_AA00.data.pal.o \
	../model/happy_mask_salesman/mask_05_B200.data.pal.o \
	../model/happy_mask_salesman/mask_06_BA00.data.pal.o \
	../model/happy_mask_salesman/mask_07_C200.data.pal.o \
	../model/happy_mask_salesman/mask_08_CA00.data.pal.o \
	../model/happy_mask_salesman/mask_09_D200.data.pal.o \
	../model/happy_mask_salesman/maskmaster_00_0.data.pal.o \
	../model/happy_mask_salesman/maskmaster_01_4A00.data.pal.o \
	../model/happy_mask_salesman/maskmaster_e00_6A00.data.pal.o \
	../model/happy_mask_salesman/maskmaster_m00_7A00.data.pal.o

examples/happy_mask_salesman.c: $(patsubst %.o,%.h,$(HAPPY_MASK_SALESMAN_RES))
happy_mask_salesman.elf: start.o examples/happy_mask_salesman.o ../math/cos_table_fp12.o ../math/cos.o $(HAPPY_MASK_SALESMAN_RES)

CFLAGS += -I../include -I../

include arm9.mk
include ../common.mk
