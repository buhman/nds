all: main.nds

MAIN_OBJ = \
	header.o \
	start.o \
	main.o

main.elf: $(MAIN_OBJ)

include arm9.mk
include common.mk
