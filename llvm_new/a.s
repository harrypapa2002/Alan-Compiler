	.text
	.file	"a.ll"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	fo@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.globl	fo                              # -- Begin function fo
	.p2align	4, 0x90
	.type	fo,@function
fo:                                     # @fo
	.cfi_startproc
# %bb.0:                                # %fo_entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$112, %rsp
	.cfi_def_cfa_offset 128
	.cfi_offset %rbx, -16
	movl	$10, 4(%rsp)
	leaq	8(%rsp), %rbx
	movl	$10, %edi
	movq	%rbx, %rsi
	callq	readString@PLT
	movq	%rbx, %rdi
	callq	writeString@PLT
	addq	$112, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	fo, .Lfunc_end1-fo
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
