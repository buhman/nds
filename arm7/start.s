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
	// copy .text to internal ram
        ldr r0, =__text_load_start
        ldr r1, =__text_link_start
        ldr r10, =__text_link_end
	COPY_32_BYTE_ALIGNED

	// jump to internal ram
	ldr 	r3,=_loop_forever
	bx	r3

_loop_forever:
	b 	_loop_forever
