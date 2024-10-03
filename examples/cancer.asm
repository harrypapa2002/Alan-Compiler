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
	bl	_cancer
	mov	w0, wzr
	ldp	x29, x30, [sp], #16             ; 16-byte Folded Reload
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_cancer                         ; -- Begin function cancer
	.p2align	2
_cancer:                                ; @cancer
	.cfi_startproc
; %bb.0:                                ; %cancer_entry
	sub	sp, sp, #80
	.cfi_def_cfa_offset 80
	stp	x20, x19, [sp, #48]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #64]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
Lloh0:
	adrp	x0, l_global_str@PAGE
Lloh1:
	add	x0, x0, l_global_str@PAGEOFF
	str	wzr, [sp, #44]
	stur	xzr, [sp, #21]
	stur	xzr, [sp, #13]
	stur	xzr, [sp, #29]
	stur	wzr, [sp, #37]
	sturh	wzr, [sp, #41]
	strb	wzr, [sp, #43]
	bl	_writeString
	add	x1, sp, #13
	mov	w0, #30
	add	x19, sp, #13
	bl	_readString
	str	wzr, [sp, #44]
LBB1_1:                                 ; %cond
                                        ; =>This Inner Loop Header: Depth=1
	ldrsw	x0, [sp, #44]
	ldrb	w8, [x19, x0]
	cbz	w8, LBB1_3
; %bb.2:                                ; %loop
                                        ;   in Loop: Header=BB1_1 Depth=1
	add	w8, w0, #1
	str	w8, [sp, #44]
	b	LBB1_1
LBB1_3:                                 ; %afterloop
	add	x1, sp, #13
                                        ; kill: def $w0 killed $w0 killed $x0
	bl	_is_it
Lloh2:
	adrp	x8, l_global_str.2@PAGE
Lloh3:
	add	x8, x8, l_global_str.2@PAGEOFF
Lloh4:
	adrp	x9, l_global_str.1@PAGE
Lloh5:
	add	x9, x9, l_global_str.1@PAGEOFF
	cmp	w0, #1
	csel	x0, x9, x8, eq
	bl	_writeString
	ldp	x29, x30, [sp, #64]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #48]             ; 16-byte Folded Reload
	add	sp, sp, #80
	ret
	.loh AdrpAdd	Lloh0, Lloh1
	.loh AdrpAdd	Lloh4, Lloh5
	.loh AdrpAdd	Lloh2, Lloh3
	.cfi_endproc
                                        ; -- End function
	.globl	_is_it                          ; -- Begin function is_it
	.p2align	2
_is_it:                                 ; @is_it
	.cfi_startproc
; %bb.0:                                ; %is_it_entry
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	sub	w8, w0, #1
	str	x1, [sp, #16]
	str	wzr, [sp, #12]
	str	w8, [sp, #28]
LBB2_1:                                 ; %cond
                                        ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #28]
	ldr	w9, [sp, #12]
	cmp	w8, #0
	cinc	w8, w8, lt
	asr	w8, w8, #1
	add	w8, w8, #1
	cmp	w9, w8
	b.gt	LBB2_4
; %bb.2:                                ; %loop
                                        ;   in Loop: Header=BB2_1 Depth=1
	ldrsw	x8, [sp, #12]
	ldr	w9, [sp, #28]
	ldr	x10, [sp, #16]
	sub	w9, w9, w8
	ldrb	w8, [x10, x8]
	ldrb	w9, [x10, w9, sxtw]
	cmp	w8, w9
	b.ne	LBB2_5
; %bb.3:                                ; %ifcont
                                        ;   in Loop: Header=BB2_1 Depth=1
	ldr	w8, [sp, #12]
	add	w8, w8, #1
	str	w8, [sp, #12]
	b	LBB2_1
LBB2_4:
	mov	w0, wzr
	add	sp, sp, #32
	ret
LBB2_5:
	mov	w0, #1
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_global_str:                           ; @global_str
	.asciz	"Give a string with maximum length 30: "

l_global_str.1:                         ; @global_str.1
	.asciz	"\nIs not palindrome...\n"

l_global_str.2:                         ; @global_str.2
	.asciz	"\nIs palindrome...\n"

.subsections_via_symbols
