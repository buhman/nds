__text_link_start = ADDR(.text);
__text_link_end = ADDR(.text) + SIZEOF(.text);
__text_load_start = LOADADDR(.text);

__data_link_start = ADDR(.data);
__data_link_end = ADDR(.data) + SIZEOF(.data);
__data_load_start = LOADADDR(.data);

__rodata_link_start = ADDR(.rodata);
__rodata_link_end = ADDR(.rodata) + SIZEOF(.rodata);
__rodata_load_start = LOADADDR(.rodata);

__bss_link_start = ADDR(.bss);
__bss_link_end = ADDR(.bss) + SIZEOF(.bss);
