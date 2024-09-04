OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
MEMORY
{
  ram : ORIGIN = 0x02000000, LENGTH = 4M
}
SECTIONS
{
  . = ORIGIN(ram) + 0x390000;

  .text ALIGN(4) :
  {
    KEEP(*(.text.start))
    *(.text)
    *(.text.*)
    *(.glue_7t)
    *(.glue_7)
    *(.vfp11_veneer)
    *(.v4_bx)
  } > ram

  .data ALIGN(4) :
  {
    *(.data)
    *(.data.*)
  } > ram

  .rodata ALIGN(4) :
  {
    *(.rodata)
    *(.rodata.*)
  } > ram

  .ctors ALIGN(4) :
  {
    KEEP(*(.ctors))
    KEEP(*(.ctors.*))
  } > ram

  .bss ALIGN(4) (NOLOAD) :
  {
    *(.bss)
    *(.bss.*)
    *(COMMON)
  } > ram

  INCLUDE "../debug.lds"
}

INCLUDE "../symbols.lds"
