        .macro FILL_ZERO_32_BYTE_ALIGNED
        cmp r1, r10
        beq _fill_break.\@
        .irp i, 2, 3, 4, 5, 6, 7, 8, 9
        mov r\i, #0
        .endr
_fill_loop.\@:
        stmia r1!, {r2 - r9}
        cmp r1, r10
        blt _fill_loop.\@
_fill_break.\@:
        .endm

        .macro COPY_32_BYTE_ALIGNED
        cmp r1, r10
        beq _fill_break.\@
_fill_loop.\@:
        ldmia r0!, {r2 - r9}
        stmia r1!, {r2 - r9}
        cmp r1, r10
        bne _fill_loop.\@
_fill_break.\@:
        .endm

        .section .text.9start
        .global _start
_start:
	/*
_link_text:
        ldr r0, =__text_load_start
        ldr r1, =__text_link_start
        ldr r10, =__text_link_end
        COPY_32_BYTE_ALIGNED

_link_data:
        ldr r0, =__data_load_start
        ldr r1, =__data_link_start
        ldr r10, =__data_link_end
        COPY_32_BYTE_ALIGNED

_link_rodata:
        ldr r0, =__rodata_load_start
        ldr r1, =__rodata_link_start
        ldr r10, =__rodata_link_end
        COPY_32_BYTE_ALIGNED
	*/

_link_bss:
        ldr r1, =__bss_link_start
        ldr r10, =__bss_link_end
        FILL_ZERO_32_BYTE_ALIGNED

_c_runtime:
	/* set stack pointer */
        ldr sp, =0x23ffffc

	/* jump to main */
        ldr r0, =main
        bx r0

	.section .text.7start
	.global _7start
_7start:
	mov r1, #0x7
	b _7start
