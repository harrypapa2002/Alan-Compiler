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
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	stp	x20, x19, [sp, #16]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
Lloh0:
	adrp	x0, l_global_str@PAGE
Lloh1:
	add	x0, x0, l_global_str@PAGEOFF
	str	xzr, [sp, #8]
	str	wzr, [sp, #4]
	bl	_writeString
	bl	_readInteger
	mov	w8, #2
	mov	w9, #1
Lloh2:
	adrp	x19, l_global_str.2@PAGE
Lloh3:
	add	x19, x19, l_global_str.2@PAGEOFF
Lloh4:
	adrp	x20, l_global_str.3@PAGE
Lloh5:
	add	x20, x20, l_global_str.3@PAGEOFF
	stp	w8, w0, [sp, #8]
	str	w9, [sp, #4]
	b	LBB1_3
LBB1_1:                                 ; %ifcont
                                        ;   in Loop: Header=BB1_3 Depth=1
	ldr	w0, [sp, #8]
	str	wzr, [sp, #4]
	bl	_writeInteger
	mov	w0, #10
	bl	_writeChar
LBB1_2:                                 ; %ifcont8
                                        ;   in Loop: Header=BB1_3 Depth=1
	ldr	w8, [sp, #8]
	add	w8, w8, #1
	str	w8, [sp, #8]
LBB1_3:                                 ; %cond
                                        ; =>This Inner Loop Header: Depth=1
	ldp	w9, w8, [sp, #8]
	cmp	w8, #0
	cinc	w8, w8, lt
	cmp	w9, w8, asr #1
	b.gt	LBB1_7
; %bb.4:                                ; %loop
                                        ;   in Loop: Header=BB1_3 Depth=1
	ldp	w9, w8, [sp, #8]
	sdiv	w10, w8, w9
	msub	w8, w10, w9, w8
	cbnz	w8, LBB1_2
; %bb.5:                                ; %then
                                        ;   in Loop: Header=BB1_3 Depth=1
	ldr	w8, [sp, #4]
	cbz	w8, LBB1_1
; %bb.6:                                ; %then4
                                        ;   in Loop: Header=BB1_3 Depth=1
	mov	x0, x19
	bl	_writeString
	ldr	w0, [sp, #12]
	bl	_writeInteger
	mov	x0, x20
	bl	_writeString
	b	LBB1_1
LBB1_7:                                 ; %afterloop
	ldr	w8, [sp, #4]
	cbz	w8, LBB1_9
; %bb.8:                                ; %then12
	ldr	w0, [sp, #12]
	bl	_writeInteger
Lloh6:
	adrp	x0, l_global_str.4@PAGE
Lloh7:
	add	x0, x0, l_global_str.4@PAGEOFF
	bl	_writeString
LBB1_9:                                 ; %ifcont16
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.loh AdrpAdd	Lloh4, Lloh5
	.loh AdrpAdd	Lloh2, Lloh3
	.loh AdrpAdd	Lloh0, Lloh1
	.loh AdrpAdd	Lloh6, Lloh7
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_global_str:                           ; @global_str
	.asciz	"Enter value of N > "

l_global_str.2:                         ; @global_str.2
	.asciz	"The non-trivial factors of "

l_global_str.3:                         ; @global_str.3
	.asciz	" are: \n"

l_global_str.4:                         ; @global_str.4
	.asciz	" is prime\n"

.subsections_via_symbols
