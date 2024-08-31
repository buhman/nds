OPT = -Os

all: main.nds

res/%.h: res/%.data
	$(BUILD_BINARY_H)

res/%.pal.h: res/%.data.pal
	$(BUILD_BINARY_H)

MAIN_OBJ = \
	header.o \
	start.o \
	main.o \
	res/player.data.o \
	res/player.data.pal.o

main.elf: $(MAIN_OBJ)

include arm9.mk
include common.mk
