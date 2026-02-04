	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 26, 0	sdk_version 26, 2
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #128
	stp	x29, x30, [sp, #112]            ; 16-byte Folded Spill
	add	x29, sp, #112
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	wzr, [x29, #-4]
	fmov	d0, #1.50000000
	stur	d0, [x29, #-16]
	fmov	d0, #2.50000000
	stur	d0, [x29, #-24]
	movi	d0, #0000000000000000
	stur	d0, [x29, #-32]
	stur	d0, [x29, #-40]
	mov	w0, #6                          ; =0x6
	add	x1, sp, #56
	bl	_clock_gettime
	str	wzr, [sp, #36]
	b	LBB0_1
LBB0_1:                                 ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #36]
	mov	w9, #57600                      ; =0xe100
	movk	w9, #1525, lsl #16
	subs	w8, w8, w9
	b.ge	LBB0_4
	b	LBB0_2
LBB0_2:                                 ;   in Loop: Header=BB0_1 Depth=1
	ldur	d0, [x29, #-16]
	ldur	d1, [x29, #-24]
	ldur	d2, [x29, #-32]
	fmadd	d0, d0, d1, d2
	stur	d0, [x29, #-32]
	ldur	d0, [x29, #-16]
	ldur	d1, [x29, #-24]
	ldur	d2, [x29, #-40]
	fmadd	d0, d0, d1, d2
	stur	d0, [x29, #-40]
	b	LBB0_3
LBB0_3:                                 ;   in Loop: Header=BB0_1 Depth=1
	ldr	w8, [sp, #36]
	add	w8, w8, #1
	str	w8, [sp, #36]
	b	LBB0_1
LBB0_4:
	mov	w0, #6                          ; =0x6
	add	x1, sp, #40
	bl	_clock_gettime
	ldr	x8, [sp, #40]
	ldr	x9, [sp, #56]
	subs	x8, x8, x9
	scvtf	d0, x8
	ldr	x8, [sp, #48]
	ldr	x9, [sp, #64]
	subs	x8, x8, x9
	scvtf	d1, x8
	mov	x8, #225833675390976            ; =0xcd6500000000
	movk	x8, #16845, lsl #48
	fmov	d2, x8
	fdiv	d1, d1, d2
	fadd	d0, d0, d1
	str	d0, [sp, #24]
	ldr	d0, [sp, #24]
	mov	x8, sp
	str	d0, [x8]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	ldur	d1, [x29, #-32]
	ldur	d0, [x29, #-40]
	mov	x8, sp
	str	d1, [x8]
	str	d0, [x8, #8]
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	bl	_printf
	mov	w0, #0                          ; =0x0
	ldp	x29, x30, [sp, #112]            ; 16-byte Folded Reload
	add	sp, sp, #128
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Time: %.6f seconds\n"

l_.str.1:                               ; @.str.1
	.asciz	"x = %f, y = %f\n"

.subsections_via_symbols
