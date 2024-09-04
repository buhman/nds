OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
MEMORY
{
  rom : ORIGIN = 0x00000000, LENGTH = 4M
}
SECTIONS
{
  . = 0x00000000;

  _start = .;

  .text.header ALIGN(4) :
  {
    KEEP(*(.text.header))
  } AT>rom

  . = 0x02000000;

  _arm9 = .;

  .text.arm9 ALIGN(4) :
  {
    KEEP(*(.data.arm9*.bin))
  } AT>rom

  . = 0x02000000 + 0x390000;

  _arm7 = .;

  .text.arm7 ALIGN(4) :
  {
    KEEP(*(.data.arm7*.bin))
  } AT>rom

  /DISCARD/ :
  {
  *(.glue_7) *(.glue_7t) *(.vfp11_veneer) *(.v4_bx)
  }

  INCLUDE "debug.lds"
}

/* header symbols */
_arm9_offset = LOADADDR(.text.arm9);
_arm9_entry = ADDR(.text.arm9);
_arm9_addr = ADDR(.text.arm9);
_arm9_size = SIZEOF(.text.arm9);

_arm7_offset = LOADADDR(.text.arm7);
_arm7_entry = ADDR(.text.arm7);
_arm7_addr = ADDR(.text.arm7);
_arm7_size = SIZEOF(.text.arm7);

_rom_size = SIZEOF(.text.header) + SIZEOF(.text.arm9) + SIZEOF(.text.arm7);
_header_size = SIZEOF(.text.header);
