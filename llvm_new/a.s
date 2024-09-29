	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:                                ; %entry
	stp	x29, x30, [sp, #-16]!           ; 16-byte Folded Spill
	.cfi_def_cfa_offset 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	bl	_main.1
	mov	w0, wzr
	ldp	x29, x30, [sp], #16             ; 16-byte Folded Reload
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main.1                         ; -- Begin function main.1
	.p2align	2
_main.1:                                ; @main.1
	.cfi_startproc
; %bb.0:                                ; %main_entry
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	movi.2d	v0, #0000000000000000
	add	x8, sp, #16
Lloh0:
	adrp	x1, l_global_str@PAGE
Lloh1:
	add	x1, x1, l_global_str@PAGEOFF
	add	x0, sp, #8
	str	x8, [sp, #8]
	stp	q0, q0, [sp, #16]
	bl	_reverse
	add	x0, sp, #16
	bl	_writeString
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	add	sp, sp, #64
	ret
	.loh AdrpAdd	Lloh0, Lloh1
	.cfi_endproc
                                        ; -- End function
	.globl	_reverse                        ; -- Begin function reverse
	.p2align	2
_reverse:                               ; @reverse
	.cfi_startproc
; %bb.0:                                ; %reverse_entry
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	ldr	x8, [x0]
	mov	x0, x1
	stp	xzr, x1, [sp, #8]
	str	x8, [sp, #24]
	bl	_strlen
	stp	w0, wzr, [sp, #8]
LBB2_1:                                 ; %cond
                                        ; =>This Inner Loop Header: Depth=1
	ldp	w9, w8, [sp, #8]
	cmp	w8, w9
	b.ge	LBB2_3
; %bb.2:                                ; %loop
                                        ;   in Loop: Header=BB2_1 Depth=1
	ldp	w9, w8, [sp, #8]
                                        ; kill: def $w8 killed $w8 def $x8
	sxtw	x8, w8
	mvn	w10, w8
	add	w11, w8, #1
	add	w9, w10, w9
	ldr	x10, [sp, #16]
	str	w11, [sp, #12]
	ldrb	w9, [x10, w9, sxtw]
	ldr	x10, [sp, #24]
	strb	w9, [x10, x8]
	b	LBB2_1
LBB2_3:                                 ; %afterloop
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	ldrsw	x8, [sp, #12]
	ldr	x9, [sp, #24]
	strb	wzr, [x9, x8]
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_global_str:                           ; @global_str
	.asciz	"\n!dlrow olleH"

.subsections_via_symbols
