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
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	str	xzr, [sp, #8]
	bl	_readInteger
	str	w0, [sp, #12]
	bl	_fibonacci
	str	w0, [sp, #8]
Lloh0:
	adrp	x0, l_global_str@PAGE
Lloh1:
	add	x0, x0, l_global_str@PAGEOFF
	bl	_writeString
	ldr	w0, [sp, #12]
	bl	_writeInteger
Lloh2:
	adrp	x0, l_global_str.2@PAGE
Lloh3:
	add	x0, x0, l_global_str.2@PAGEOFF
	bl	_writeString
	ldr	w0, [sp, #8]
	bl	_writeInteger
Lloh4:
	adrp	x0, l_global_str.3@PAGE
Lloh5:
	add	x0, x0, l_global_str.3@PAGEOFF
	bl	_writeString
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.loh AdrpAdd	Lloh4, Lloh5
	.loh AdrpAdd	Lloh2, Lloh3
	.loh AdrpAdd	Lloh0, Lloh1
	.cfi_endproc
                                        ; -- End function
	.globl	_fibonacci                      ; -- Begin function fibonacci
	.p2align	2
_fibonacci:                             ; @fibonacci
	.cfi_startproc
; %bb.0:                                ; %fibonacci_entry
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	stp	x20, x19, [sp, #16]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	str	w0, [sp, #12]
	cbz	w0, LBB2_4
; %bb.1:                                ; %else
	ldr	w8, [sp, #12]
	cmp	w8, #1
	b.ne	LBB2_3
; %bb.2:
	mov	w0, #1
	b	LBB2_4
LBB2_3:                                 ; %else6
	ldr	w8, [sp, #12]
	sub	w0, w8, #1
	bl	_fibonacci
	ldr	w8, [sp, #12]
	mov	w19, w0
	sub	w0, w8, #2
	bl	_fibonacci
	add	w0, w19, w0
LBB2_4:                                 ; %common.ret
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_global_str:                           ; @global_str
	.asciz	"Fibonacci of "

l_global_str.2:                         ; @global_str.2
	.asciz	" is "

l_global_str.3:                         ; @global_str.3
	.asciz	"\n"

.subsections_via_symbols
