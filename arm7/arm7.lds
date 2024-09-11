OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
MEMORY
{
  main_memory : ORIGIN = 0x02390000, LENGTH = 256K
  arm7_exclusive_internal_work_ram : ORIGIN = 0x03800000, LENGTH = 64K
}
SECTIONS
{
  . = ORIGIN(arm7_exclusive_internal_work_ram);

  .text ALIGN(4) :
  {
    KEEP(*(.text.start))
    *(.text)
    *(.text.*)
    . = ALIGN(32);
  } > arm7_exclusive_internal_work_ram AT> main_memory

  .data ALIGN(4) :
  {
    *(.data)
    *(.data.*)
  } > arm7_exclusive_internal_work_ram AT> main_memory

  .rodata ALIGN(4) :
  {
    *(.rodata)
    *(.rodata.*)
  } > arm7_exclusive_internal_work_ram AT> main_memory

  .ctors ALIGN(4) :
  {
    KEEP(*(.ctors))
    KEEP(*(.ctors.*))
  } > arm7_exclusive_internal_work_ram AT> main_memory

  .bss ALIGN(4) (NOLOAD) :
  {
    *(.bss)
    *(.bss.*)
    *(COMMON)
  } > arm7_exclusive_internal_work_ram

  /DISCARD/ :
  {
    *(.glue_7) *(.glue_7t) *(.vfp11_veneer) *(.v4_bx)
  }

  INCLUDE "../debug.lds"
}

INCLUDE "../symbols.lds"
