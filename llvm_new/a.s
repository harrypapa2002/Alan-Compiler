	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:                                ; %entry
	stp	x29, x30, [sp, #-16]!           ; 16-byte Folded Spill
	.cfi_def_cfa_offset 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	bl	_gcd
	mov	w0, wzr
	ldp	x29, x30, [sp], #16             ; 16-byte Folded Reload
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_gcd                            ; -- Begin function gcd
	.p2align	2
_gcd:                                   ; @gcd
	.cfi_startproc
; %bb.0:                                ; %gcd_entry
	sub	sp, sp, #160
	.cfi_def_cfa_offset 160
	stp	x29, x30, [sp, #144]            ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
Lloh0:
	adrp	x8, l_global_str@PAGE
Lloh1:
	add	x8, x8, l_global_str@PAGEOFF
	add	x0, sp, #96
	ldr	q0, [x8]
	ldur	q1, [x8, #9]
	str	q0, [sp, #96]
	stur	q1, [sp, #105]
	bl	_writeString
	bl	_readInteger
Lloh2:
	adrp	x8, l_global_str.1@PAGE
Lloh3:
	add	x8, x8, l_global_str.1@PAGEOFF
	str	w0, [sp, #92]
	str	w0, [sp, #140]
	add	x0, sp, #64
	ldr	q0, [x8]
	ldur	q1, [x8, #10]
	str	q0, [sp, #64]
	stur	q1, [sp, #74]
	bl	_writeString
	bl	_readInteger
Lloh4:
	adrp	x9, l_global_str.2@PAGE
Lloh5:
	add	x9, x9, l_global_str.2@PAGEOFF
	mov	w8, #32
	str	w0, [sp, #60]
	str	w0, [sp, #136]
	add	x0, sp, #16
	ldp	q0, q1, [x9]
	strh	w8, [sp, #48]
	stp	q0, q1, [sp, #16]
	bl	_writeString
	ldp	w1, w0, [sp, #136]
	bl	_find_gcd
	str	w0, [sp, #12]
	bl	_writeInteger
	ldp	x29, x30, [sp, #144]            ; 16-byte Folded Reload
	add	sp, sp, #160
	ret
	.loh AdrpAdd	Lloh4, Lloh5
	.loh AdrpAdd	Lloh2, Lloh3
	.loh AdrpAdd	Lloh0, Lloh1
	.cfi_endproc
                                        ; -- End function
	.globl	_find_gcd                       ; -- Begin function find_gcd
	.p2align	2
_find_gcd:                              ; @find_gcd
	.cfi_startproc
; %bb.0:                                ; %find_gcd_entry
	stp	x29, x30, [sp, #-16]!           ; 16-byte Folded Spill
	.cfi_def_cfa_offset 16
	mov	x29, sp
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	sub	sp, sp, #16
	cmp	w0, w1
	stp	w1, w0, [x29, #-8]
	cset	w8, gt
	sturb	w8, [x29, #-16]
	ldur	w8, [x29, #-16]
	cbz	w8, LBB2_2
; %bb.1:                                ; %then
	ldur	w8, [x29, #-4]
	b	LBB2_3
LBB2_2:                                 ; %else
	ldur	w8, [x29, #-8]
LBB2_3:                                 ; %cond.preheader
	stur	w8, [x29, #-12]
	mov	w8, #1
LBB2_4:                                 ; %cond
                                        ; =>This Inner Loop Header: Depth=1
	mov	x9, sp
	sub	x10, x9, #16
	mov	sp, x10
	mov	x10, sp
	stur	w8, [x9, #-16]
	sub	x11, x10, #16
	mov	sp, x11
	ldur	w11, [x29, #-12]
	mov	w9, w8
	cmp	w11, w9
	cset	w9, gt
	sturb	w9, [x10, #-16]
	sub	x9, sp, #16
	ldur	w10, [x10, #-16]
	mov	sp, x9
	cbz	w10, LBB2_7
; %bb.5:                                ; %loop
                                        ;   in Loop: Header=BB2_4 Depth=1
	ldur	w10, [x29, #-4]
	ldur	w11, [x29, #-12]
	sdiv	w12, w10, w11
	msub	w10, w12, w11, w10
	str	w10, [x9]
	mov	x10, sp
	sub	x11, x10, #16
	mov	sp, x11
	mov	x11, sp
	stur	wzr, [x10, #-16]
	sub	x12, x11, #16
	mov	sp, x12
	ldr	w9, [x9]
	mov	w10, wzr
	cmp	w9, w10
	cset	w9, eq
	sturb	w9, [x11, #-16]
	mov	x9, sp
	sub	x10, x9, #16
	mov	sp, x10
	ldp	w12, w10, [x29, #-12]
	sdiv	w13, w10, w12
	msub	w10, w13, w12, w10
	stur	w10, [x9, #-16]
	mov	x10, sp
	sub	x12, x10, #16
	mov	sp, x12
	mov	x12, sp
	stur	wzr, [x10, #-16]
	sub	x13, x12, #16
	mov	sp, x13
	ldur	w9, [x9, #-16]
	mov	w10, wzr
	cmp	w9, w10
	cset	w9, eq
	sturb	w9, [x12, #-16]
	mov	x9, sp
	sub	x10, x9, #16
	mov	sp, x10
	ldur	w10, [x11, #-16]
	ldur	w11, [x12, #-16]
	ands	w10, w10, w11
	stur	w10, [x9, #-16]
	b.ne	LBB2_8
; %bb.6:                                ; %ifcont15
                                        ;   in Loop: Header=BB2_4 Depth=1
	mov	x9, sp
	sub	x10, x9, #16
	mov	sp, x10
	mov	x10, sp
	stur	w8, [x9, #-16]
	sub	x11, x10, #16
	mov	sp, x11
	ldur	w11, [x29, #-12]
	mov	w9, w8
	sub	w9, w11, w9
	stur	w9, [x10, #-16]
	stur	w9, [x29, #-12]
	b	LBB2_4
LBB2_7:                                 ; %afterloop
	mov	w0, #1
	str	w0, [x9]
	b	LBB2_9
LBB2_8:                                 ; %then13
	ldur	w0, [x29, #-12]
LBB2_9:                                 ; %common.ret
	mov	sp, x29
	ldp	x29, x30, [sp], #16             ; 16-byte Folded Reload
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_global_str:                           ; @global_str
	.asciz	"Give the first integer: "

l_global_str.1:                         ; @global_str.1
	.asciz	"Give the second integer: "

l_global_str.2:                         ; @global_str.2
	.asciz	"\\nThe gcd you are looking for is "

.subsections_via_symbols
