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
	sub	sp, sp, #112
	.cfi_def_cfa_offset 112
	stp	x28, x27, [sp, #16]             ; 16-byte Folded Spill
	stp	x26, x25, [sp, #32]             ; 16-byte Folded Spill
	stp	x24, x23, [sp, #48]             ; 16-byte Folded Spill
	stp	x22, x21, [sp, #64]             ; 16-byte Folded Spill
	stp	x20, x19, [sp, #80]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #96]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	.cfi_offset w23, -56
	.cfi_offset w24, -64
	.cfi_offset w25, -72
	.cfi_offset w26, -80
	.cfi_offset w27, -88
	.cfi_offset w28, -96
	mov	w22, #21846
	mov	w23, #26215
	mov	w24, #43691
	mov	w25, #43690
	mov	w26, #21844
	mov	w27, #52429
	mov	w28, #39321
	mov	w21, #13106
	movk	w22, #21845, lsl #16
	movk	w23, #26214, lsl #16
Lloh0:
	adrp	x19, l_global_str@PAGE
Lloh1:
	add	x19, x19, l_global_str@PAGEOFF
	movk	w24, #43690, lsl #16
	movk	w25, #10922, lsl #16
	movk	w26, #21845, lsl #16
	movk	w27, #52428, lsl #16
	movk	w28, #6553, lsl #16
	movk	w21, #13107, lsl #16
Lloh2:
	adrp	x20, l_global_str.2@PAGE
Lloh3:
	add	x20, x20, l_global_str.2@PAGEOFF
	str	wzr, [sp, #12]
LBB1_1:                                 ; %cond
                                        ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #12]
	cmp	w8, #99
	b.gt	LBB1_11
; %bb.2:                                ; %loop
                                        ;   in Loop: Header=BB1_1 Depth=1
	ldr	w8, [sp, #12]
	add	w8, w8, #1
	smull	x9, w8, w22
	smull	x10, w8, w23
	str	w8, [sp, #12]
	lsr	x11, x9, #63
	lsr	x9, x9, #32
	lsr	x12, x10, #63
	asr	x10, x10, #33
	add	w9, w9, w11
	add	w10, w10, w12
	add	w9, w9, w9, lsl #1
	add	w10, w10, w10, lsl #2
	sub	w9, w8, w9
	sub	w10, w8, w10
	orr	w9, w9, w10
	cbnz	w9, LBB1_4
; %bb.3:                                ; %then
                                        ;   in Loop: Header=BB1_1 Depth=1
	mov	x0, x19
	bl	_writeString
	b	LBB1_9
LBB1_4:                                 ; %else
                                        ;   in Loop: Header=BB1_1 Depth=1
	ldr	w8, [sp, #12]
	madd	w8, w8, w24, w25
	cmp	w8, w26
	b.hi	LBB1_6
; %bb.5:                                ; %then9
                                        ;   in Loop: Header=BB1_1 Depth=1
	mov	x0, x20
	bl	_writeString
	b	LBB1_9
LBB1_6:                                 ; %else11
                                        ;   in Loop: Header=BB1_1 Depth=1
	ldr	w8, [sp, #12]
	madd	w8, w8, w27, w28
	cmp	w8, w21
	b.hi	LBB1_8
; %bb.7:                                ; %then15
                                        ;   in Loop: Header=BB1_1 Depth=1
Lloh4:
	adrp	x0, l_global_str.3@PAGE
Lloh5:
	add	x0, x0, l_global_str.3@PAGEOFF
	bl	_writeString
	b	LBB1_9
LBB1_8:                                 ; %else17
                                        ;   in Loop: Header=BB1_1 Depth=1
	ldr	w0, [sp, #12]
	bl	_writeInteger
LBB1_9:                                 ; %ifcont19
                                        ;   in Loop: Header=BB1_1 Depth=1
	ldr	w8, [sp, #12]
	cmp	w8, #100
	b.eq	LBB1_1
; %bb.10:                               ; %then21
                                        ;   in Loop: Header=BB1_1 Depth=1
	mov	w0, #32
	bl	_writeChar
	b	LBB1_1
LBB1_11:                                ; %afterloop
	mov	w0, #10
	bl	_writeChar
	ldp	x29, x30, [sp, #96]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #80]             ; 16-byte Folded Reload
	ldp	x22, x21, [sp, #64]             ; 16-byte Folded Reload
	ldp	x24, x23, [sp, #48]             ; 16-byte Folded Reload
	ldp	x26, x25, [sp, #32]             ; 16-byte Folded Reload
	ldp	x28, x27, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #112
	ret
	.loh AdrpAdd	Lloh2, Lloh3
	.loh AdrpAdd	Lloh0, Lloh1
	.loh AdrpAdd	Lloh4, Lloh5
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_global_str:                           ; @global_str
	.asciz	"FizzBuzz"

l_global_str.2:                         ; @global_str.2
	.asciz	"Fizz"

l_global_str.3:                         ; @global_str.3
	.asciz	"Buzz"

.subsections_via_symbols
