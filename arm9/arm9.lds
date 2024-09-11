OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
MEMORY
{
  main_memory : ORIGIN = 0x02000000, LENGTH = 4M - 256K
  arm9_instruction_tcm : ORIGIN = 0x01000000, LENGTH = 32K
  arm9_data_tcm : ORIGIN = 0x027e0000, LENGTH = 16K
}
SECTIONS
{
  . = ORIGIN(arm9_instruction_tcm);

  .text ALIGN(4) :
  {
    KEEP(*(.text.start))
    *(.text)
    *(.text.*)
    . = ALIGN(32);
  } > arm9_instruction_tcm AT> main_memory

  . = ORIGIN(main_memory) + SIZEOF(.text);

  .data ALIGN(4) :
  {
    *(.data)
    *(.data.*)
  } > main_memory

  .rodata ALIGN(4) :
  {
    *(.rodata)
    *(.rodata.*)
  } > main_memory

  .bss ALIGN(4) (NOLOAD) :
  {
    *(.bss)
    *(.bss.*)
    *(COMMON)
  } > main_memory

  /DISCARD/ :
  {
    *(.glue_7) *(.glue_7t) *(.vfp11_veneer) *(.v4_bx)
  }

  INCLUDE "../debug.lds"
}

INCLUDE "../symbols.lds"
INCLUDE "addresses.lds"

__stack_end = ORIGIN(main_memory) + LENGTH(main_memory) - 4;
