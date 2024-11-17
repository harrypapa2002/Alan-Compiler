	.text
	.file	"fibonacci.imm"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	main.1@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.globl	main.1                          # -- Begin function main.1
	.p2align	4, 0x90
	.type	main.1,@function
main.1:                                 # @main.1
	.cfi_startproc
# %bb.0:                                # %main_entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$0, 4(%rsp)
	movl	$0, (%rsp)
	callq	readInteger@PLT
	movl	%eax, 4(%rsp)
	movl	%eax, %edi
	callq	fibonacci@PLT
	movl	%eax, (%rsp)
	movl	$.Lglobal_str, %edi
	callq	writeString@PLT
	movl	4(%rsp), %edi
	callq	writeInteger@PLT
	movl	$.Lglobal_str.2, %edi
	callq	writeString@PLT
	movl	(%rsp), %edi
	callq	writeInteger@PLT
	movl	$.Lglobal_str.3, %edi
	callq	writeString@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main.1, .Lfunc_end1-main.1
	.cfi_endproc
                                        # -- End function
	.globl	fibonacci                       # -- Begin function fibonacci
	.p2align	4, 0x90
	.type	fibonacci,@function
fibonacci:                              # @fibonacci
	.cfi_startproc
# %bb.0:                                # %fibonacci_entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -16
	movl	%edi, 12(%rsp)
	testl	%edi, %edi
	jne	.LBB2_3
# %bb.1:                                # %then
	xorl	%eax, %eax
	jmp	.LBB2_2
.LBB2_3:                                # %else
	cmpl	$1, 12(%rsp)
	jne	.LBB2_5
# %bb.4:                                # %then4
	movl	$1, %eax
	jmp	.LBB2_2
.LBB2_5:                                # %else6
	movl	12(%rsp), %edi
	decl	%edi
	callq	fibonacci@PLT
	movl	%eax, %ebx
	movl	12(%rsp), %edi
	addl	$-2, %edi
	callq	fibonacci@PLT
	addl	%ebx, %eax
.LBB2_2:                                # %then
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end2:
	.size	fibonacci, .Lfunc_end2-fibonacci
	.cfi_endproc
                                        # -- End function
	.type	.Lglobal_str,@object            # @global_str
	.section	.rodata.str1.1,"aMS",@progbits,1
.Lglobal_str:
	.asciz	"Fibonacci of "
	.size	.Lglobal_str, 14

	.type	.Lglobal_str.2,@object          # @global_str.2
.Lglobal_str.2:
	.asciz	" is "
	.size	.Lglobal_str.2, 5

	.type	.Lglobal_str.3,@object          # @global_str.3
.Lglobal_str.3:
	.asciz	"\n"
	.size	.Lglobal_str.3, 2

	.section	".note.GNU-stack","",@progbits
