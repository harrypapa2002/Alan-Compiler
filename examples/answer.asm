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
	stp	x29, x30, [sp, #-16]!           ; 16-byte Folded Spill
	.cfi_def_cfa_offset 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	bl	_readInteger
Lloh0:
	adrp	x8, l_global_str.2@PAGE
Lloh1:
	add	x8, x8, l_global_str.2@PAGEOFF
Lloh2:
	adrp	x9, l_global_str@PAGE
Lloh3:
	add	x9, x9, l_global_str@PAGEOFF
	cmp	w0, #42
	csel	x0, x9, x8, eq
	bl	_writeString
	ldp	x29, x30, [sp], #16             ; 16-byte Folded Reload
	ret
	.loh AdrpAdd	Lloh2, Lloh3
	.loh AdrpAdd	Lloh0, Lloh1
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_global_str:                           ; @global_str
	.asciz	"The answer to the ultimate question of Life, the Universe, and Everything is 42.\n"

l_global_str.2:                         ; @global_str.2
	.asciz	"I'm sorry, I don't understand the question.\n"

.subsections_via_symbols
