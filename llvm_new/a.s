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
	sub	sp, sp, #96
	.cfi_def_cfa_offset 96
	stp	x29, x30, [sp, #80]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	movi.2d	v0, #0000000000000000
	mov	w8, #5
	add	x9, sp, #22
	add	x10, sp, #32
	mov	x0, sp
	add	x2, sp, #36
	mov	w1, wzr
	str	wzr, [sp, #76]
	stur	xzr, [sp, #68]
	stur	xzr, [sp, #22]
	stur	q0, [sp, #36]
	stur	q0, [sp, #52]
	strh	wzr, [sp, #30]
	str	w8, [sp, #32]
	stp	x9, x10, [sp]
	bl	_reverse
Lloh0:
	adrp	x0, l_global_str.25@PAGE
Lloh1:
	add	x0, x0, l_global_str.25@PAGEOFF
	bl	_writeString
	ldr	w0, [sp, #76]
	bl	_writeInteger
Lloh2:
	adrp	x0, l_global_str.26@PAGE
Lloh3:
	add	x0, x0, l_global_str.26@PAGEOFF
	bl	_writeString
Lloh4:
	adrp	x0, l_global_str.27@PAGE
Lloh5:
	add	x0, x0, l_global_str.27@PAGEOFF
	bl	_writeString
	ldr	w0, [sp, #56]
	bl	_writeInteger
Lloh6:
	adrp	x0, l_global_str.28@PAGE
Lloh7:
	add	x0, x0, l_global_str.28@PAGEOFF
	bl	_writeString
	ldr	w8, [sp, #32]
Lloh8:
	adrp	x0, l_global_str.29@PAGE
Lloh9:
	add	x0, x0, l_global_str.29@PAGEOFF
	add	w8, w8, #1
	str	w8, [sp, #32]
	bl	_writeString
	ldr	w0, [sp, #32]
	bl	_writeInteger
Lloh10:
	adrp	x0, l_global_str.30@PAGE
Lloh11:
	add	x0, x0, l_global_str.30@PAGEOFF
	bl	_writeString
	ldrb	w8, [sp, #27]
	cmp	w8, #99
	b.ne	LBB1_2
; %bb.1:                                ; %then
Lloh12:
	adrp	x0, l_global_str.31@PAGE
Lloh13:
	add	x0, x0, l_global_str.31@PAGEOFF
	bl	_writeString
	ldrb	w0, [sp, #27]
	bl	_writeChar
Lloh14:
	adrp	x0, l_global_str.32@PAGE
Lloh15:
	add	x0, x0, l_global_str.32@PAGEOFF
	bl	_writeString
	mov	w8, #100
	strb	w8, [sp, #27]
LBB1_2:                                 ; %ifcont
Lloh16:
	adrp	x0, l_global_str.33@PAGE
Lloh17:
	add	x0, x0, l_global_str.33@PAGEOFF
	bl	_writeString
	ldrb	w0, [sp, #27]
	bl	_writeChar
Lloh18:
	adrp	x0, l_global_str.34@PAGE
Lloh19:
	add	x0, x0, l_global_str.34@PAGEOFF
	bl	_writeString
	ldp	x29, x30, [sp, #80]             ; 16-byte Folded Reload
	add	sp, sp, #96
	ret
	.loh AdrpAdd	Lloh10, Lloh11
	.loh AdrpAdd	Lloh8, Lloh9
	.loh AdrpAdd	Lloh6, Lloh7
	.loh AdrpAdd	Lloh4, Lloh5
	.loh AdrpAdd	Lloh2, Lloh3
	.loh AdrpAdd	Lloh0, Lloh1
	.loh AdrpAdd	Lloh14, Lloh15
	.loh AdrpAdd	Lloh12, Lloh13
	.loh AdrpAdd	Lloh18, Lloh19
	.loh AdrpAdd	Lloh16, Lloh17
	.cfi_endproc
                                        ; -- End function
	.globl	_reverse                        ; -- Begin function reverse
	.p2align	2
_reverse:                               ; @reverse
	.cfi_startproc
; %bb.0:                                ; %reverse_entry
	sub	sp, sp, #80
	.cfi_def_cfa_offset 80
	stp	x29, x30, [sp, #64]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	ldp	x9, x10, [x0]
	add	x8, sp, #44
	mov	x0, sp
	str	w1, [sp, #44]
	stp	x9, x2, [sp]
	stp	x10, x2, [sp, #24]
	stp	x10, x9, [sp, #48]
	str	x8, [sp, #16]
	bl	_innerIncrement
	ldr	w8, [sp, #44]
Lloh20:
	adrp	x0, l_global_str.17@PAGE
Lloh21:
	add	x0, x0, l_global_str.17@PAGEOFF
	ldr	x9, [sp, #48]
	add	w8, w8, #10
	str	w8, [sp, #44]
	ldr	w8, [x9]
	add	w8, w8, #9
	str	w8, [x9]
	bl	_writeString
	ldr	w0, [sp, #44]
	bl	_writeInteger
Lloh22:
	adrp	x0, l_global_str.18@PAGE
Lloh23:
	add	x0, x0, l_global_str.18@PAGEOFF
	bl	_writeString
	ldr	x8, [sp, #32]
Lloh24:
	adrp	x0, l_global_str.19@PAGE
Lloh25:
	add	x0, x0, l_global_str.19@PAGEOFF
	ldr	w9, [x8, #20]
	add	w9, w9, #10
	str	w9, [x8, #20]
	bl	_writeString
	ldr	x8, [sp, #32]
	ldr	w0, [x8, #20]
	bl	_writeInteger
Lloh26:
	adrp	x0, l_global_str.20@PAGE
Lloh27:
	add	x0, x0, l_global_str.20@PAGEOFF
	bl	_writeString
Lloh28:
	adrp	x0, l_global_str.21@PAGE
Lloh29:
	add	x0, x0, l_global_str.21@PAGEOFF
	bl	_writeString
	ldr	x8, [sp, #48]
	ldr	w0, [x8]
	bl	_writeInteger
Lloh30:
	adrp	x0, l_global_str.22@PAGE
Lloh31:
	add	x0, x0, l_global_str.22@PAGEOFF
	bl	_writeString
	ldr	x8, [sp, #56]
	ldrb	w8, [x8, #5]
	cmp	w8, #98
	b.ne	LBB2_2
; %bb.1:                                ; %then
Lloh32:
	adrp	x0, l_global_str.23@PAGE
Lloh33:
	add	x0, x0, l_global_str.23@PAGEOFF
	bl	_writeString
	ldr	x8, [sp, #56]
	ldrb	w0, [x8, #5]
	bl	_writeChar
Lloh34:
	adrp	x0, l_global_str.24@PAGE
Lloh35:
	add	x0, x0, l_global_str.24@PAGEOFF
	bl	_writeString
	ldr	x8, [sp, #56]
	mov	w9, #99
	strb	w9, [x8, #5]
LBB2_2:                                 ; %ifcont
	ldp	x29, x30, [sp, #64]             ; 16-byte Folded Reload
	add	sp, sp, #80
	ret
	.loh AdrpAdd	Lloh30, Lloh31
	.loh AdrpAdd	Lloh28, Lloh29
	.loh AdrpAdd	Lloh26, Lloh27
	.loh AdrpAdd	Lloh24, Lloh25
	.loh AdrpAdd	Lloh22, Lloh23
	.loh AdrpAdd	Lloh20, Lloh21
	.loh AdrpAdd	Lloh34, Lloh35
	.loh AdrpAdd	Lloh32, Lloh33
	.cfi_endproc
                                        ; -- End function
	.globl	_innerIncrement                 ; -- Begin function innerIncrement
	.p2align	2
_innerIncrement:                        ; @innerIncrement
	.cfi_startproc
; %bb.0:                                ; %innerIncrement_entry
	sub	sp, sp, #80
	.cfi_def_cfa_offset 80
	stp	x29, x30, [sp, #64]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	ldp	x8, x9, [x0]
	ldp	x10, x11, [x0, #16]
	mov	x0, sp
	stp	x9, x8, [sp, #48]
	stp	x8, x9, [sp]
	stp	x11, x10, [sp, #32]
	stp	x10, x11, [sp, #16]
	bl	_foo
	ldp	x10, x8, [sp, #32]
Lloh36:
	adrp	x0, l_global_str.9@PAGE
Lloh37:
	add	x0, x0, l_global_str.9@PAGEOFF
	ldr	w9, [x8]
	add	w9, w9, #3
	str	w9, [x8]
	ldr	w8, [x10]
	add	w8, w8, #20
	str	w8, [x10]
	bl	_writeString
	ldr	x8, [sp, #40]
	ldr	w0, [x8]
	bl	_writeInteger
Lloh38:
	adrp	x0, l_global_str.10@PAGE
Lloh39:
	add	x0, x0, l_global_str.10@PAGEOFF
	bl	_writeString
	ldr	x8, [sp, #48]
Lloh40:
	adrp	x0, l_global_str.11@PAGE
Lloh41:
	add	x0, x0, l_global_str.11@PAGEOFF
	ldr	w9, [x8, #20]
	add	w9, w9, #3
	str	w9, [x8, #20]
	bl	_writeString
	ldr	x8, [sp, #48]
	ldr	w0, [x8, #20]
	bl	_writeInteger
Lloh42:
	adrp	x0, l_global_str.12@PAGE
Lloh43:
	add	x0, x0, l_global_str.12@PAGEOFF
	bl	_writeString
Lloh44:
	adrp	x0, l_global_str.13@PAGE
Lloh45:
	add	x0, x0, l_global_str.13@PAGEOFF
	bl	_writeString
	ldr	x8, [sp, #32]
	ldr	w0, [x8]
	bl	_writeInteger
Lloh46:
	adrp	x0, l_global_str.14@PAGE
Lloh47:
	add	x0, x0, l_global_str.14@PAGEOFF
	bl	_writeString
	ldr	x8, [sp, #56]
	ldrb	w8, [x8, #5]
	cmp	w8, #97
	b.ne	LBB3_2
; %bb.1:                                ; %then
Lloh48:
	adrp	x0, l_global_str.15@PAGE
Lloh49:
	add	x0, x0, l_global_str.15@PAGEOFF
	bl	_writeString
	ldr	x8, [sp, #56]
	ldrb	w0, [x8, #5]
	bl	_writeChar
Lloh50:
	adrp	x0, l_global_str.16@PAGE
Lloh51:
	add	x0, x0, l_global_str.16@PAGEOFF
	bl	_writeString
	ldr	x8, [sp, #56]
	mov	w9, #98
	strb	w9, [x8, #5]
LBB3_2:                                 ; %ifcont
	ldp	x29, x30, [sp, #64]             ; 16-byte Folded Reload
	add	sp, sp, #80
	ret
	.loh AdrpAdd	Lloh46, Lloh47
	.loh AdrpAdd	Lloh44, Lloh45
	.loh AdrpAdd	Lloh42, Lloh43
	.loh AdrpAdd	Lloh40, Lloh41
	.loh AdrpAdd	Lloh38, Lloh39
	.loh AdrpAdd	Lloh36, Lloh37
	.loh AdrpAdd	Lloh50, Lloh51
	.loh AdrpAdd	Lloh48, Lloh49
	.cfi_endproc
                                        ; -- End function
	.globl	_foo                            ; -- Begin function foo
	.p2align	2
_foo:                                   ; @foo
	.cfi_startproc
; %bb.0:                                ; %foo_entry
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	ldp	x10, x8, [x0, #16]
	ldp	x11, x12, [x0]
Lloh52:
	adrp	x0, l_global_str@PAGE
Lloh53:
	add	x0, x0, l_global_str@PAGEOFF
	ldr	w9, [x8]
	stp	x8, x10, [sp]
	stp	x12, x11, [sp, #16]
	add	w9, w9, #7
	str	w9, [x8]
	ldr	w9, [x10]
	add	w9, w9, #1
	str	w9, [x10]
	bl	_writeString
	ldr	x8, [sp, #8]
	ldr	w0, [x8]
	bl	_writeInteger
Lloh54:
	adrp	x0, l_global_str.2@PAGE
Lloh55:
	add	x0, x0, l_global_str.2@PAGEOFF
	bl	_writeString
	ldr	x8, [sp, #16]
Lloh56:
	adrp	x0, l_global_str.3@PAGE
Lloh57:
	add	x0, x0, l_global_str.3@PAGEOFF
	ldr	w9, [x8, #20]
	add	w9, w9, #1
	str	w9, [x8, #20]
	bl	_writeString
	ldr	x8, [sp, #16]
	ldr	w0, [x8, #20]
	bl	_writeInteger
Lloh58:
	adrp	x0, l_global_str.4@PAGE
Lloh59:
	add	x0, x0, l_global_str.4@PAGEOFF
	bl	_writeString
Lloh60:
	adrp	x0, l_global_str.5@PAGE
Lloh61:
	add	x0, x0, l_global_str.5@PAGEOFF
	bl	_writeString
	ldr	x8, [sp]
	ldr	w0, [x8]
	bl	_writeInteger
Lloh62:
	adrp	x0, l_global_str.6@PAGE
Lloh63:
	add	x0, x0, l_global_str.6@PAGEOFF
	bl	_writeString
	ldr	x8, [sp, #24]
	mov	w9, #97
Lloh64:
	adrp	x0, l_global_str.7@PAGE
Lloh65:
	add	x0, x0, l_global_str.7@PAGEOFF
	strb	w9, [x8, #5]
	bl	_writeString
	ldr	x8, [sp, #24]
	ldrb	w0, [x8, #5]
	bl	_writeChar
Lloh66:
	adrp	x0, l_global_str.8@PAGE
Lloh67:
	add	x0, x0, l_global_str.8@PAGEOFF
	bl	_writeString
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.loh AdrpAdd	Lloh66, Lloh67
	.loh AdrpAdd	Lloh64, Lloh65
	.loh AdrpAdd	Lloh62, Lloh63
	.loh AdrpAdd	Lloh60, Lloh61
	.loh AdrpAdd	Lloh58, Lloh59
	.loh AdrpAdd	Lloh56, Lloh57
	.loh AdrpAdd	Lloh54, Lloh55
	.loh AdrpAdd	Lloh52, Lloh53
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_global_str:                           ; @global_str
	.asciz	"u in foo = "

l_global_str.2:                         ; @global_str.2
	.asciz	"\n"

l_global_str.3:                         ; @global_str.3
	.asciz	"v[5] in foo = "

l_global_str.4:                         ; @global_str.4
	.asciz	"\n"

l_global_str.5:                         ; @global_str.5
	.asciz	"r in foo = "

l_global_str.6:                         ; @global_str.6
	.asciz	"\n"

l_global_str.7:                         ; @global_str.7
	.asciz	"arr[5] in foo = "

l_global_str.8:                         ; @global_str.8
	.asciz	"\n"

l_global_str.9:                         ; @global_str.9
	.asciz	"u in innerIncrement = "

l_global_str.10:                        ; @global_str.10
	.asciz	"\n"

l_global_str.11:                        ; @global_str.11
	.asciz	"v[5] in innerIncrement = "

l_global_str.12:                        ; @global_str.12
	.asciz	"\n"

l_global_str.13:                        ; @global_str.13
	.asciz	"r in innerIncrement = "

l_global_str.14:                        ; @global_str.14
	.asciz	"\n"

l_global_str.15:                        ; @global_str.15
	.asciz	"arr[5] in innerIncrement = "

l_global_str.16:                        ; @global_str.16
	.asciz	"\n"

l_global_str.17:                        ; @global_str.17
	.asciz	"u in reverse = "

l_global_str.18:                        ; @global_str.18
	.asciz	"\n"

l_global_str.19:                        ; @global_str.19
	.asciz	"v[5] in reverse = "

l_global_str.20:                        ; @global_str.20
	.asciz	"\n"

l_global_str.21:                        ; @global_str.21
	.asciz	"r in reverse = "

l_global_str.22:                        ; @global_str.22
	.asciz	"\n"

l_global_str.23:                        ; @global_str.23
	.asciz	"arr[5] in reverse = "

l_global_str.24:                        ; @global_str.24
	.asciz	"\n"

l_global_str.25:                        ; @global_str.25
	.asciz	"y in main = "

l_global_str.26:                        ; @global_str.26
	.asciz	"\n"

l_global_str.27:                        ; @global_str.27
	.asciz	"z[5] in main = "

l_global_str.28:                        ; @global_str.28
	.asciz	"\n"

l_global_str.29:                        ; @global_str.29
	.asciz	"r in main = "

l_global_str.30:                        ; @global_str.30
	.asciz	"\n"

l_global_str.31:                        ; @global_str.31
	.asciz	"arr[5] in main = "

l_global_str.32:                        ; @global_str.32
	.asciz	"\n"

l_global_str.33:                        ; @global_str.33
	.asciz	"arr[5] in main = "

l_global_str.34:                        ; @global_str.34
	.asciz	"\n"

.subsections_via_symbols
