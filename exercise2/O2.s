	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 26, 0	sdk_version 26, 2
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #80
	stp	x29, x30, [sp, #64]             ; 16-byte Folded Spill
	add	x29, sp, #64
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	sub	x1, x29, #16
	mov	w0, #6                          ; =0x6
	bl	_clock_gettime
	movi.2d	v1, #0000000000000000
	mov	w8, #57600                      ; =0xe100
	movk	w8, #1525, lsl #16
	fmov.2d	v0, #3.75000000
LBB0_1:                                 ; =>This Inner Loop Header: Depth=1
	fadd.2d	v1, v1, v0
	fadd.2d	v1, v1, v0
	fadd.2d	v1, v1, v0
	fadd.2d	v1, v1, v0
	subs	w8, w8, #4
	b.ne	LBB0_1
; %bb.2:
	add	x1, sp, #32
	mov	w0, #6                          ; =0x6
	str	q1, [sp, #16]                   ; 16-byte Folded Spill
	bl	_clock_gettime
	ldp	x8, x9, [sp, #32]
	ldp	x10, x11, [x29, #-16]
	sub	x8, x8, x10
	scvtf	d0, x8
	sub	x8, x9, x11
	scvtf	d1, x8
	mov	x8, #225833675390976            ; =0xcd6500000000
	movk	x8, #16845, lsl #48
	fmov	d2, x8
	fdiv	d1, d1, d2
	fadd	d0, d1, d0
	str	d0, [sp]
Lloh0:
	adrp	x0, l_.str@PAGE
Lloh1:
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	ldr	q0, [sp, #16]                   ; 16-byte Folded Reload
	str	q0, [sp]
Lloh2:
	adrp	x0, l_.str.1@PAGE
Lloh3:
	add	x0, x0, l_.str.1@PAGEOFF
	bl	_printf
	mov	w0, #0                          ; =0x0
	ldp	x29, x30, [sp, #64]             ; 16-byte Folded Reload
	add	sp, sp, #80
	ret
	.loh AdrpAdd	Lloh2, Lloh3
	.loh AdrpAdd	Lloh0, Lloh1
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Time: %.6f seconds\n"

l_.str.1:                               ; @.str.1
	.asciz	"x = %f, y = %f\n"

.subsections_via_symbols
