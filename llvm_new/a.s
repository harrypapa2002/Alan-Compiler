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
	sub	sp, sp, #112
	.cfi_def_cfa_offset 112
	stp	x29, x30, [sp, #96]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	mov	w9, #61643
	mov	w12, #65
	mov	w8, #137
	movk	w9, #10381, lsl #16
	mov	w10, #101
	add	x11, sp, #28
	str	w12, [sp, #92]
	str	wzr, [sp, #12]
LBB1_1:                                 ; %cond
                                        ; =>This Inner Loop Header: Depth=1
	ldr	w12, [sp, #12]
	cmp	w12, #15
	b.gt	LBB1_3
; %bb.2:                                ; %loop
                                        ;   in Loop: Header=BB1_1 Depth=1
	ldr	w12, [sp, #92]
	ldr	w13, [sp, #12]
	ldrsw	x14, [sp, #12]
	madd	w12, w12, w8, w13
	add	w13, w13, #1
	add	w12, w12, #220
	str	w13, [sp, #12]
	smull	x15, w12, w9
	lsr	x16, x15, #63
	asr	x15, x15, #36
	add	w15, w15, w16
	msub	w12, w15, w10, w12
	str	w12, [x11, x14, lsl #2]
	str	w12, [sp, #92]
	b	LBB1_1
LBB1_3:                                 ; %afterloop
Lloh0:
	adrp	x0, l_global_str.3@PAGE
Lloh1:
	add	x0, x0, l_global_str.3@PAGEOFF
	add	x2, sp, #28
	mov	w1, #16
	bl	_writeArray
	add	x1, sp, #28
	mov	w0, #16
	bl	_bsort
Lloh2:
	adrp	x0, l_global_str.4@PAGE
Lloh3:
	add	x0, x0, l_global_str.4@PAGEOFF
	add	x2, sp, #28
	mov	w1, #16
	bl	_writeArray
	ldp	x29, x30, [sp, #96]             ; 16-byte Folded Reload
	add	sp, sp, #112
	ret
	.loh AdrpAdd	Lloh2, Lloh3
	.loh AdrpAdd	Lloh0, Lloh1
	.cfi_endproc
                                        ; -- End function
	.globl	_bsort                          ; -- Begin function bsort
	.p2align	2
_bsort:                                 ; @bsort
	.cfi_startproc
; %bb.0:                                ; %bsort_entry
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	stp	x20, x19, [sp, #32]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	mov	w19, #121
	mov	w20, #110
	str	w0, [sp, #28]
	str	x1, [sp, #16]
	strb	w19, [sp, #15]
LBB2_1:                                 ; %cond
                                        ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB2_4 Depth 2
	ldrb	w8, [sp, #15]
	cmp	w8, #121
	b.ne	LBB2_7
; %bb.2:                                ; %loop
                                        ;   in Loop: Header=BB2_1 Depth=1
	strb	w20, [sp, #15]
	str	wzr, [sp, #8]
	b	LBB2_4
LBB2_3:                                 ; %ifcont
                                        ;   in Loop: Header=BB2_4 Depth=2
	ldr	w8, [sp, #8]
	add	w8, w8, #1
	str	w8, [sp, #8]
LBB2_4:                                 ; %cond3
                                        ;   Parent Loop BB2_1 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	w8, [sp, #28]
	ldr	w9, [sp, #8]
	sub	w8, w8, #1
	cmp	w9, w8
	b.ge	LBB2_1
; %bb.5:                                ; %loop7
                                        ;   in Loop: Header=BB2_4 Depth=2
	ldrsw	x8, [sp, #8]
	ldr	x9, [sp, #16]
	add	w10, w8, #1
	ldr	w8, [x9, x8, lsl #2]
	ldr	w9, [x9, w10, sxtw #2]
	add	w8, w8, #1
	add	w9, w9, #1
	cmp	w8, w9
	b.le	LBB2_3
; %bb.6:                                ; %then
                                        ;   in Loop: Header=BB2_4 Depth=2
	ldrsw	x8, [sp, #8]
	ldr	x9, [sp, #16]
	add	w10, w8, #1
	add	x0, x9, x8, lsl #2
	add	x1, x9, w10, sxtw #2
	bl	_swap
	strb	w19, [sp, #15]
	b	LBB2_3
LBB2_7:                                 ; %afterloop24
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #64
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_swap                           ; -- Begin function swap
	.p2align	2
_swap:                                  ; @swap
	.cfi_startproc
; %bb.0:                                ; %swap_entry
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	ldr	w8, [x0]
	stp	x1, x0, [sp, #16]
	ldr	w9, [x1]
	str	w8, [sp, #12]
	str	w9, [x0]
	str	w8, [x1]
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_writeArray                     ; -- Begin function writeArray
	.p2align	2
_writeArray:                            ; @writeArray
	.cfi_startproc
; %bb.0:                                ; %writeArray_entry
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	stp	x20, x19, [sp, #32]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	str	w1, [sp, #20]
	str	x0, [sp, #24]
	str	x2, [sp, #8]
	bl	_writeString
Lloh4:
	adrp	x19, l_global_str@PAGE
Lloh5:
	add	x19, x19, l_global_str@PAGEOFF
	str	wzr, [sp, #4]
	b	LBB4_2
LBB4_1:                                 ; %ifcont
                                        ;   in Loop: Header=BB4_2 Depth=1
	ldrsw	x8, [sp, #4]
	ldr	x9, [sp, #8]
	ldr	w0, [x9, x8, lsl #2]
	bl	_writeInteger
	ldr	w8, [sp, #4]
	add	w8, w8, #1
	str	w8, [sp, #4]
LBB4_2:                                 ; %cond
                                        ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #4]
	ldr	w9, [sp, #20]
	cmp	w8, w9
	b.ge	LBB4_5
; %bb.3:                                ; %loop
                                        ;   in Loop: Header=BB4_2 Depth=1
	ldr	w8, [sp, #4]
	cmp	w8, #1
	b.lt	LBB4_1
; %bb.4:                                ; %then
                                        ;   in Loop: Header=BB4_2 Depth=1
	mov	x0, x19
	bl	_writeString
	b	LBB4_1
LBB4_5:                                 ; %afterloop
Lloh6:
	adrp	x0, l_global_str.2@PAGE
Lloh7:
	add	x0, x0, l_global_str.2@PAGEOFF
	bl	_writeString
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #64
	ret
	.loh AdrpAdd	Lloh4, Lloh5
	.loh AdrpAdd	Lloh6, Lloh7
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_global_str:                           ; @global_str
	.asciz	", "

l_global_str.2:                         ; @global_str.2
	.asciz	"\n"

l_global_str.3:                         ; @global_str.3
	.asciz	"Initial array: "

l_global_str.4:                         ; @global_str.4
	.asciz	"Sorted array: "

.subsections_via_symbols
