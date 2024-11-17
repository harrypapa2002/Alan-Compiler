	.text
	.file	"factorial.imm"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	factorial@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.globl	factorial                       # -- Begin function factorial
	.p2align	4, 0x90
	.type	factorial,@function
factorial:                              # @factorial
	.cfi_startproc
# %bb.0:                                # %factorial_entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$0, 4(%rsp)
	movl	$7, %edi
	callq	factorial.1@PLT
	movl	%eax, 4(%rsp)
	movl	$.Lglobal_str, %edi
	callq	writeString@PLT
	movl	4(%rsp), %edi
	callq	writeInteger@PLT
	movl	$.Lglobal_str.2, %edi
	callq	writeString@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	factorial, .Lfunc_end1-factorial
	.cfi_endproc
                                        # -- End function
	.globl	factorial.1                     # -- Begin function factorial.1
	.p2align	4, 0x90
	.type	factorial.1,@function
factorial.1:                            # @factorial.1
	.cfi_startproc
# %bb.0:                                # %factorial_entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	%edi, 4(%rsp)
	testl	%edi, %edi
	jne	.LBB2_2
# %bb.1:                                # %then
	movl	$1, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.LBB2_2:                                # %else
	.cfi_def_cfa_offset 16
	movl	4(%rsp), %edi
	decl	%edi
	callq	factorial.1@PLT
	imull	4(%rsp), %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end2:
	.size	factorial.1, .Lfunc_end2-factorial.1
	.cfi_endproc
                                        # -- End function
	.type	.Lglobal_str,@object            # @global_str
	.section	.rodata.str1.1,"aMS",@progbits,1
.Lglobal_str:
	.asciz	"The factorial of 7 is "
	.size	.Lglobal_str, 23

	.type	.Lglobal_str.2,@object          # @global_str.2
.Lglobal_str.2:
	.asciz	"\n"
	.size	.Lglobal_str.2, 2

	.section	".note.GNU-stack","",@progbits
