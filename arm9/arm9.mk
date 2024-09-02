TARGET = arm-none-eabi-
AARCH = -march=armv5te+nofp -mlittle-endian
CARCH = -march=armv5te+nofp -mtune=arm946e-s -mlittle-endian -mno-thumb-interwork
OBJARCH = -O elf32-littlearm -B armv5te
LDSCRIPT = arm9.lds
