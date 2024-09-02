TARGET = arm-none-eabi-
AARCH = -march=armv4t -mlittle-endian
CARCH = -march=armv4t -mtune=arm7tdmi -mlittle-endian -mno-thumb-interwork
OBJARCH = -O elf32-littlearm -B armv4t
LDSCRIPT = arm7.lds
