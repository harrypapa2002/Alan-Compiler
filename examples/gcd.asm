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
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
Lloh0:
	adrp	x0, l_global_str@PAGE
Lloh1:
	add	x0, x0, l_global_str@PAGEOFF
	str	xzr, [sp, #8]
	bl	_writeString
	bl	_readInteger
	str	w0, [sp, #12]
Lloh2:
	adrp	x0, l_global_str.1@PAGE
Lloh3:
	add	x0, x0, l_global_str.1@PAGEOFF
	bl	_writeString
	bl	_readInteger
	str	w0, [sp, #8]
Lloh4:
	adrp	x0, l_global_str.2@PAGE
Lloh5:
	add	x0, x0, l_global_str.2@PAGEOFF
	bl	_writeString
	ldr	w1, [sp, #8]
	add	x0, sp, #12
	bl	_find_gcd
	bl	_writeInteger
Lloh6:
	adrp	x0, l_global_str.3@PAGE
Lloh7:
	add	x0, x0, l_global_str.3@PAGEOFF
	bl	_writeString
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.loh AdrpAdd	Lloh6, Lloh7
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
	stp	wzr, w1, [sp, #-16]!
	.cfi_def_cfa_offset 16
	ldr	w8, [x0]
	str	x0, [sp, #8]
	cmp	w8, w1
	b.le	LBB2_2
; %bb.1:                                ; %then
	ldr	x8, [sp, #8]
	ldr	w8, [x8]
	b	LBB2_3
LBB2_2:                                 ; %else
	ldr	w8, [sp, #4]
LBB2_3:                                 ; %cond.preheader
                                        ; =>This Inner Loop Header: Depth=1
	str	w8, [sp]
	mov	w8, w8
	cmp	w8, #2
	b.lt	LBB2_6
; %bb.4:                                ; %loop
                                        ;   in Loop: Header=BB2_3 Depth=1
	ldr	x8, [sp, #8]
	ldp	w0, w10, [sp]
	ldr	w8, [x8]
	sdiv	w11, w10, w0
	sdiv	w9, w8, w0
	msub	w8, w9, w0, w8
	msub	w9, w11, w0, w10
	orr	w8, w8, w9
	cbz	w8, LBB2_7
; %bb.5:                                ; %ifcont17
                                        ;   in Loop: Header=BB2_3 Depth=1
	sub	w8, w0, #1
	b	LBB2_3
LBB2_6:
	mov	w0, #1
LBB2_7:                                 ; %common.ret
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_global_str:                           ; @global_str
	.asciz	"Give the first integer: "

l_global_str.1:                         ; @global_str.1
	.asciz	"Give the second integer: "

l_global_str.2:                         ; @global_str.2
	.asciz	"\nThe gcd you are looking for is: "

l_global_str.3:                         ; @global_str.3
	.asciz	"\n"

.subsections_via_symbols
