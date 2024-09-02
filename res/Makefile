OBJ += $(patsubst %.data,%.data.o,$(wildcard *.data))
OBJ += $(patsubst %.data.pal,%.data.pal.o,$(wildcard *.data.pal))

HEADER += $(patsubst %.data,%.data.h,$(wildcard *.data))
HEADER += $(patsubst %.data.pal,%.data.pal.h,$(wildcard *.data.pal))

TARGET=arm-none-eabi-
OBJARCH=-O elf32-littlearm -B armv5te

all: $(OBJ) $(HEADER)

include ../common.mk

%.data.h: %.data
	$(BUILD_BINARY_H)

%.data.pal.h: %.data.pal
	$(BUILD_BINARY_H)
