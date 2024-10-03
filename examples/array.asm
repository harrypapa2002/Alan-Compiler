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
	ldrsw	x8, [sp, #44]
	ldrb	w8, [x19, x8]
	cbz	w8, LBB1_3
; %bb.2:                                ; %loop
                                        ;   in Loop: Header=BB1_1 Depth=1
	ldrsw	x8, [sp, #44]
	ldrb	w0, [x19, x8]
	bl	_writeChar
	ldr	w8, [sp, #44]
	add	w8, w8, #1
	str	w8, [sp, #44]
	b	LBB1_1
LBB1_3:                                 ; %afterloop
	ldp	x29, x30, [sp, #64]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #48]             ; 16-byte Folded Reload
	add	sp, sp, #80
	ret
	.loh AdrpAdd	Lloh0, Lloh1
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_global_str:                           ; @global_str
	.asciz	"Give a string with maximum length 30: "

.subsections_via_symbols
