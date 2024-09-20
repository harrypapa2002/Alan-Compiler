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
	sub	sp, sp, #80
	.cfi_def_cfa_offset 80
	stp	x29, x30, [sp, #64]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	add	x8, sp, #28
	add	x9, sp, #32
Lloh0:
	adrp	x1, l_global_str.3@PAGE
Lloh1:
	add	x1, x1, l_global_str.3@PAGEOFF
	add	x0, sp, #8
	stp	x8, x9, [sp, #8]
	bl	_reverse
	add	x0, sp, #32
	bl	_writeString
	ldp	x29, x30, [sp, #64]             ; 16-byte Folded Reload
	add	sp, sp, #80
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
	ldp	x8, x9, [x0]
	mov	x0, x1
	str	x1, [sp, #8]
	stp	x9, x8, [sp, #16]
	bl	_strlen
	stp	w0, wzr, [sp]
LBB2_1:                                 ; %cond
                                        ; =>This Inner Loop Header: Depth=1
	ldp	w9, w8, [sp]
	cmp	w8, w9
	b.ge	LBB2_3
; %bb.2:                                ; %loop
                                        ;   in Loop: Header=BB2_1 Depth=1
	ldp	w9, w8, [sp]
                                        ; kill: def $w8 killed $w8 def $x8
	sxtw	x8, w8
	mvn	w10, w8
	add	w11, w8, #1
	add	w9, w10, w9
	ldr	x10, [sp, #8]
	str	w11, [sp, #4]
	ldrb	w9, [x10, w9, sxtw]
	ldr	x10, [sp, #16]
	strb	w9, [x10, x8]
	b	LBB2_1
LBB2_3:                                 ; %afterloop
	ldp	x9, x11, [sp, #16]
	mov	w10, #5
Lloh2:
	adrp	x0, l_global_str@PAGE
Lloh3:
	add	x0, x0, l_global_str@PAGEOFF
	ldrsw	x8, [sp, #4]
	strb	wzr, [x9, x8]
	str	w10, [x11]
	bl	_writeString
	ldr	x8, [sp, #24]
	ldr	w0, [x8]
	bl	_writeInteger
Lloh4:
	adrp	x0, l_global_str.2@PAGE
Lloh5:
	add	x0, x0, l_global_str.2@PAGEOFF
	bl	_writeString
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.loh AdrpAdd	Lloh4, Lloh5
	.loh AdrpAdd	Lloh2, Lloh3
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_global_str:                           ; @global_str
	.asciz	"k = "

l_global_str.2:                         ; @global_str.2
	.asciz	"\n"

l_global_str.3:                         ; @global_str.3
	.asciz	"\n!dlrow olleH"

.subsections_via_symbols
