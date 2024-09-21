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
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
Lloh0:
	adrp	x0, l_global_str.7@PAGE
Lloh1:
	add	x0, x0, l_global_str.7@PAGEOFF
	str	wzr, [sp, #12]
	bl	_writeString
	ldr	w0, [sp, #12]
	bl	_writeInteger
Lloh2:
	adrp	x0, l_global_str.8@PAGE
Lloh3:
	add	x0, x0, l_global_str.8@PAGEOFF
	bl	_writeString
	add	x8, sp, #12
	mov	x0, sp
	str	x8, [sp]
	bl	_reverse
Lloh4:
	adrp	x0, l_global_str.9@PAGE
Lloh5:
	add	x0, x0, l_global_str.9@PAGEOFF
	bl	_writeString
	ldr	w0, [sp, #12]
	bl	_writeInteger
Lloh6:
	adrp	x0, l_global_str.10@PAGE
Lloh7:
	add	x0, x0, l_global_str.10@PAGEOFF
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
	.globl	_reverse                        ; -- Begin function reverse
	.p2align	2
_reverse:                               ; @reverse
	.cfi_startproc
; %bb.0:                                ; %reverse_entry
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	mov	w8, #5
	ldr	x9, [x0]
Lloh8:
	adrp	x0, l_global_str.3@PAGE
Lloh9:
	add	x0, x0, l_global_str.3@PAGEOFF
	str	x9, [sp, #8]
	str	w8, [x9]
	bl	_writeString
	ldr	x8, [sp, #8]
	ldr	w0, [x8]
	bl	_writeInteger
Lloh10:
	adrp	x0, l_global_str.4@PAGE
Lloh11:
	add	x0, x0, l_global_str.4@PAGEOFF
	bl	_writeString
	ldr	x8, [sp, #8]
	mov	x0, sp
	str	x8, [sp]
	bl	_innerIncrement
Lloh12:
	adrp	x0, l_global_str.5@PAGE
Lloh13:
	add	x0, x0, l_global_str.5@PAGEOFF
	bl	_writeString
	ldr	x8, [sp, #8]
	ldr	w0, [x8]
	bl	_writeInteger
Lloh14:
	adrp	x0, l_global_str.6@PAGE
Lloh15:
	add	x0, x0, l_global_str.6@PAGEOFF
	bl	_writeString
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.loh AdrpAdd	Lloh14, Lloh15
	.loh AdrpAdd	Lloh12, Lloh13
	.loh AdrpAdd	Lloh10, Lloh11
	.loh AdrpAdd	Lloh8, Lloh9
	.cfi_endproc
                                        ; -- End function
	.globl	_innerIncrement                 ; -- Begin function innerIncrement
	.p2align	2
_innerIncrement:                        ; @innerIncrement
	.cfi_startproc
; %bb.0:                                ; %innerIncrement_entry
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	ldr	x8, [x0]
Lloh16:
	adrp	x0, l_global_str@PAGE
Lloh17:
	add	x0, x0, l_global_str@PAGEOFF
	ldr	w9, [x8]
	str	x8, [sp, #8]
	add	w9, w9, #1
	str	w9, [x8]
	bl	_writeString
	ldr	x8, [sp, #8]
	ldr	w0, [x8]
	bl	_writeInteger
Lloh18:
	adrp	x0, l_global_str.2@PAGE
Lloh19:
	add	x0, x0, l_global_str.2@PAGEOFF
	bl	_writeString
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.loh AdrpAdd	Lloh18, Lloh19
	.loh AdrpAdd	Lloh16, Lloh17
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_global_str:                           ; @global_str
	.asciz	"y in innerIncrement = "

l_global_str.2:                         ; @global_str.2
	.asciz	"\n"

l_global_str.3:                         ; @global_str.3
	.asciz	"y in reverse = "

l_global_str.4:                         ; @global_str.4
	.asciz	"\n"

l_global_str.5:                         ; @global_str.5
	.asciz	"y in reverse after innerIncrement = "

l_global_str.6:                         ; @global_str.6
	.asciz	"\n"

l_global_str.7:                         ; @global_str.7
	.asciz	"y in main = "

l_global_str.8:                         ; @global_str.8
	.asciz	"\n"

l_global_str.9:                         ; @global_str.9
	.asciz	"y in main after reverse = "

l_global_str.10:                        ; @global_str.10
	.asciz	"\n"

.subsections_via_symbols
