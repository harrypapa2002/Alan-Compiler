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
	bl	_factorial
	mov	w0, wzr
	ldp	x29, x30, [sp], #16             ; 16-byte Folded Reload
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_factorial                      ; -- Begin function factorial
	.p2align	2
_factorial:                             ; @factorial
	.cfi_startproc
; %bb.0:                                ; %factorial_entry
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	mov	w0, #7
	str	wzr, [sp, #12]
	bl	_factorial.1
	str	w0, [sp, #12]
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
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.loh AdrpAdd	Lloh2, Lloh3
	.loh AdrpAdd	Lloh0, Lloh1
	.cfi_endproc
                                        ; -- End function
	.globl	_factorial.1                    ; -- Begin function factorial.1
	.p2align	2
_factorial.1:                           ; @factorial.1
	.cfi_startproc
; %bb.0:                                ; %factorial_entry
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	str	w0, [sp, #12]
	cbnz	w0, LBB2_2
; %bb.1:
	mov	w0, #1
	b	LBB2_3
LBB2_2:                                 ; %else
	ldr	w8, [sp, #12]
	sub	w0, w8, #1
	bl	_factorial.1
	ldr	w8, [sp, #12]
	mul	w0, w8, w0
LBB2_3:                                 ; %common.ret
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_global_str:                           ; @global_str
	.asciz	"The factorial of 7 is "

l_global_str.2:                         ; @global_str.2
	.asciz	"\n"

.subsections_via_symbols
