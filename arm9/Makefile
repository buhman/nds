OPT = -Os

OBJ = \
	start.o \
	main.o \
	../res/player.data.o \
	../res/player.data.pal.o \
	../res/bowser.data.o \
	../res/bowser.data.pal.o

all: arm9.bin

arm9.elf: $(OBJ)

CFLAGS += -I../include

include arm9.mk
include ../common.mk
