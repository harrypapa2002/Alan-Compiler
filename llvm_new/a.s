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
	callq	comp@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.globl	comp                            # -- Begin function comp
	.p2align	4, 0x90
	.type	comp,@function
comp:                                   # @comp
	.cfi_startproc
# %bb.0:                                # %comp_entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$5, -12(%rbp)
	movl	$15, -8(%rbp)
	movb	$0, -4(%rbp)
	cmpl	$0, -4(%rbp)
	je	.LBB1_2
# %bb.1:                                # %then
	movq	%rsp, %rax
	leaq	-16(%rax), %rdi
	movq	%rdi, %rsp
	movabsq	$753336325040664419, %rcx       # imm = 0xA74636572726F63
	movq	%rcx, -16(%rax)
	movb	$0, -8(%rax)
	jmp	.LBB1_3
.LBB1_2:                                # %else
	movq	%rsp, %rax
	leaq	-16(%rax), %rdi
	movq	%rdi, %rsp
	movl	$681838, -13(%rax)              # imm = 0xA676E
	movl	$1852797559, -16(%rax)          # imm = 0x6E6F7277
.LBB1_3:                                # %ifcont
	callq	writeString@PLT
	movq	%rbp, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end1:
	.size	comp, .Lfunc_end1-comp
	.cfi_endproc
                                        # -- End function
	.type	.Lglobal_str,@object            # @global_str
	.section	.rodata.str1.1,"aMS",@progbits,1
.Lglobal_str:
	.asciz	"correct\n"
	.size	.Lglobal_str, 9

	.type	.Lglobal_str.1,@object          # @global_str.1
.Lglobal_str.1:
	.asciz	"wrong\n"
	.size	.Lglobal_str.1, 7

	.section	".note.GNU-stack","",@progbits
