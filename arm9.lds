OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
MEMORY
{
  rom : ORIGIN = 0x00000000, LENGTH = 4M
  ram : ORIGIN = 0x02000000, LENGTH = 4M
}
SECTIONS
{
  . = ORIGIN(rom);

  .text.header ALIGN(4) :
  {
    KEEP(*(.text.header))
  } > rom

  . = ORIGIN(ram);

  .text.arm7 ALIGN(4) :
  {
    KEEP(*(.text.7start))
  } > ram AT> rom

  .text ALIGN(4) :
  {
    KEEP(*(.text.9start))
    *(.text)
    *(.text.*)
    *(.glue_7t)
    *(.glue_7)
    *(.vfp11_veneer)
    *(.v4_bx)
  } > ram AT> rom

  .data ALIGN(4) :
  {
    *(.data)
    *(.data.*)
  } > ram AT> rom

  .rodata ALIGN(4) :
  {
    *(.rodata)
    *(.rodata.*)
  } > ram AT> rom

  .ctors ALIGN(4) :
  {
    KEEP(*(.ctors))
    KEEP(*(.ctors.*))
  } > ram AT> rom

  .bss ALIGN(4) (NOLOAD) :
  {
    *(.bss)
    *(.bss.*)
    *(COMMON)
  } > ram AT> rom

  INCLUDE "debug.lds"
}

INCLUDE "symbols.lds"
INCLUDE "addresses_arm9.lds"
