__stack_end = ORIGIN(ram) + LENGTH(ram) - 4;

__text_link_start = ADDR(.text);
__text_link_end = ADDR(.text) + SIZEOF(.text);
__text_load_start = LOADADDR(.text);

__data_link_start = ADDR(.data);
__data_link_end = ADDR(.data) + SIZEOF(.data);
__data_load_start = LOADADDR(.data);

__rodata_link_start = ADDR(.rodata);
__rodata_link_end = ADDR(.rodata) + SIZEOF(.rodata);
__rodata_load_start = LOADADDR(.rodata);

__ctors_link_start = ADDR(.ctors);
__ctors_link_end = ADDR(.ctors) + SIZEOF(.ctors);

__bss_link_start = ADDR(.bss);
__bss_link_end = ADDR(.bss) + SIZEOF(.bss);

/* header symbols */
_arm9_offset = LOADADDR(.text);
_arm9_entry = ADDR(.text);
_arm9_addr = ADDR(.text);
_arm9_size = SIZEOF(.text) + SIZEOF(.data) + SIZEOF(.rodata) + SIZEOF(.ctors);

_arm7_offset = LOADADDR(.text.arm7);
_arm7_entry = ADDR(.text.arm7);
_arm7_addr = ADDR(.text.arm7);
_arm7_size = SIZEOF(.text.arm7);

_rom_size = SIZEOF(.text.header) + SIZEOF(.text) + SIZEOF(.data) + SIZEOF(.rodata) + SIZEOF(.ctors) + SIZEOF(.text.arm7);
_header_size = SIZEOF(.text.header);
