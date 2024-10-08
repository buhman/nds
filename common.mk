OPT ?= -Og
DEBUG = -g -gdwarf-4

AFLAGS += --fatal-warnings

CFLAGS += -falign-functions=4 -ffunction-sections -fdata-sections -fshort-enums -ffreestanding -nostdlib -fno-builtin
#-finline-stringops
CFLAGS += -Wall -Werror -Wfatal-errors
CFLAGS += -Wno-array-bounds
#CFLAGS += -Wno-error=narrowing -Wno-error=unused-variable -Wno-error=array-bounds=
CFLAGS += -Wno-error=maybe-uninitialized
CFLAGS += -Wno-error=unused-but-set-variable
CFLAGS += -Wno-error=unused-variable
CFLAGS += -Wno-aggressive-loop-optimizations
CFLAGS += -fno-inline-small-functions

CXXFLAGS += -fno-exceptions -fno-non-call-exceptions -fno-rtti -fno-threadsafe-statics

#
LDFLAGS += --gc-sections --no-warn-rwx-segment --print-memory-usage --entry=_start --orphan-handling=error --print-gc-sections

DEPFLAGS = -MMD -MP

CC = $(TARGET)gcc
CXX = $(TARGET)g++
AS = $(TARGET)as
LD = $(TARGET)ld
OBJCOPY = $(TARGET)objcopy
OBJDUMP = $(TARGET)objdump

LIBGCC = $(shell $(CC) -print-file-name=libgcc.a)

define BUILD_BINARY_O
	cd $(dir $<) ; \
	$(OBJCOPY) \
		-I binary $(OBJARCH) \
		--rename-section .data=.data.$(basename $@) \
		$(notdir $<) $(notdir $@)
endef

as_obj_binary = _binary_$(subst .,_,$(subst /,_,$(notdir $(1))))

define BUILD_BINARY_H
	@echo gen $@
	@echo '#pragma once' > $@
	@echo '#include <stdint.h>' >> $@
	@echo 'extern uint32_t $(call as_obj_binary,$<)_start __asm("$(call as_obj_binary,$<)_start");' >> $@
	@echo 'extern uint32_t $(call as_obj_binary,$<)_end __asm("$(call as_obj_binary,$<)_end");' >> $@
	@echo 'extern uint32_t $(call as_obj_binary,$<)_size __asm("$(call as_obj_binary,$<)_size");' >> $@
endef

%.bin.o: %.bin
	$(BUILD_BINARY_O)

%.pcm.o: %.pcm
	$(BUILD_BINARY_O)

%.data.o: %.data
	$(BUILD_BINARY_O)

%.data.pal.o: %.data.pal
	$(BUILD_BINARY_O)

%.o: %.s
	$(AS) $(AARCH) $(AFLAGS) $(DEBUG) $< -o $@

%.o: %.c
	$(CC) $(CARCH) $(CFLAGS) $(OPT) $(DEBUG) $(DEPFLAGS) -MF ${<}.d -c $< -o $@

%.o: %.cpp
	$(CXX) $(CARCH) $(CFLAGS) $(CXXFLAGS) $(OPT) $(DEBUG) $(DEPFLAGS) -MF ${<}.d -c $< -o $@

%.elf:
	$(LD) $(LDFLAGS) -T $(LDSCRIPT) $^ -o $@

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@
	du -b $@

%.nds: %.bin
	python patch.py $< $@

-include $(shell find -type f -name '*.d')

clean:
	find -P \
		-regextype posix-egrep \
		-regex '.*\.(nds|o|d|bin|elf|gch)$$' \
		-exec rm {} \;

.SUFFIXES:
.INTERMEDIATE:
.SECONDARY:
.PHONY: all clean

%: RCS/%,v
%: RCS/%
%: %,v
%: s.%
%: SCCS/s.%
