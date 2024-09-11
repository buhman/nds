	/* DDI0201D_arm946es_r1p1_trm.pdf pdf page 40 ; printed page 2-12 */
	.set INSTRUCTION_TCM_LOAD_MODE, (1 << 19)
	.set INSTRUCTION_TCM_ENABLE, (1 << 18)
	.set DATA_TCM_LOAD_MODE, (1 << 17)
	.set DATA_TCM_ENABLE, (1 << 16)
	.set DISABLE_LOADING_TBIT, (1 << 15)
	.set ROUND_ROBIN_REPLACEMENT, (1 << 14)
	.set ALTERNATE_VECTOR_SELET, (1 << 13)
	.set INSTRUCTION_CACHE_ENABLE, (1 << 12)
	.set BIG_ENDIAN, (1 << 7)
	.set DATA_CACHE_ENABLE, (1 << 2)
	.set PROTECTION_UNIT_ENABLE, (1 << 0)

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

        .section .text.start
        .global _start
_start:
	// https://developer.arm.com/documentation/ddi0338/g/system-control-coprocessor/system-control-processor-registers/c9--data-tcm-region-register?lang=en

	// set data tcm address
	ldr r0, =0x027e0000
	mcr p15, 0, r0, c9, c1, 0

	// enable instruction and data TCM
        mrc p15, 0, r0, c1, c0, 0
        ldr r1, =INSTRUCTION_TCM_ENABLE | DATA_TCM_ENABLE | INSTRUCTION_CACHE_ENABLE | DATA_CACHE_ENABLE
        orr r0, r0, r1
        mcr p15, 0, r0, c1, c0, 0

_link_text:
        ldr r0, =__text_load_start
        ldr r1, =__text_link_start
        ldr r10, =__text_link_end
        COPY_32_BYTE_ALIGNED

	/*
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
        ldr sp, =__stack_end

	/* jump to main */
        ldr r0, =main
        bx r0
