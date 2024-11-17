	.text
	.file	"cancer.imm"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	cancer@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.globl	cancer                          # -- Begin function cancer
	.p2align	4, 0x90
	.type	cancer,@function
cancer:                                 # @cancer
	.cfi_startproc
# %bb.0:                                # %cancer_entry
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movl	$0, 4(%rsp)
	movq	$0, 9(%rsp)
	movq	$0, 17(%rsp)
	movq	$0, 25(%rsp)
	movl	$0, 33(%rsp)
	movw	$0, 37(%rsp)
	movb	$0, 39(%rsp)
	movl	$.Lglobal_str, %edi
	callq	writeString@PLT
	leaq	9(%rsp), %rsi
	movl	$30, %edi
	callq	readString@PLT
	movl	$0, 4(%rsp)
	.p2align	4, 0x90
.LBB1_1:                                # %cond
                                        # =>This Inner Loop Header: Depth=1
	movslq	4(%rsp), %rax
	cmpb	$0, 9(%rsp,%rax)
	je	.LBB1_3
# %bb.2:                                # %loop
                                        #   in Loop: Header=BB1_1 Depth=1
	incl	4(%rsp)
	jmp	.LBB1_1
.LBB1_3:                                # %afterloop
	movl	4(%rsp), %edi
	decl	%edi
	movl	%edi, 4(%rsp)
	leaq	9(%rsp), %rsi
	callq	is_it@PLT
	cmpl	$1, %eax
	jne	.LBB1_5
# %bb.4:                                # %then
	movl	$.Lglobal_str.1, %edi
	jmp	.LBB1_6
.LBB1_5:                                # %else
	movl	$.Lglobal_str.2, %edi
.LBB1_6:                                # %ifcont
	callq	writeString@PLT
	addq	$40, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	cancer, .Lfunc_end1-cancer
	.cfi_endproc
                                        # -- End function
	.globl	is_it                           # -- Begin function is_it
	.p2align	4, 0x90
	.type	is_it,@function
is_it:                                  # @is_it
	.cfi_startproc
# %bb.0:                                # %is_it_entry
	movq	%rsi, -8(%rsp)
	movl	$0, -16(%rsp)
	decl	%edi
	movl	%edi, -12(%rsp)
	.p2align	4, 0x90
.LBB2_1:                                # %cond
                                        # =>This Inner Loop Header: Depth=1
	movl	-12(%rsp), %eax
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%eax, %ecx
	sarl	%ecx
	incl	%ecx
	cmpl	%ecx, -16(%rsp)
	jge	.LBB2_4
# %bb.2:                                # %loop
                                        #   in Loop: Header=BB2_1 Depth=1
	movslq	-16(%rsp), %rax
	movq	-8(%rsp), %rcx
	movl	-12(%rsp), %edx
	subl	%eax, %edx
	movslq	%edx, %rdx
	movzbl	(%rcx,%rax), %eax
	cmpb	(%rcx,%rdx), %al
	jne	.LBB2_5
# %bb.3:                                # %else
                                        #   in Loop: Header=BB2_1 Depth=1
	incl	-16(%rsp)
	jmp	.LBB2_1
.LBB2_4:                                # %afterloop
	xorl	%eax, %eax
	retq
.LBB2_5:                                # %then
	movl	$1, %eax
	retq
.Lfunc_end2:
	.size	is_it, .Lfunc_end2-is_it
	.cfi_endproc
                                        # -- End function
	.type	.Lglobal_str,@object            # @global_str
	.section	.rodata.str1.1,"aMS",@progbits,1
.Lglobal_str:
	.asciz	"Give a string with maximum length 30: "
	.size	.Lglobal_str, 39

	.type	.Lglobal_str.1,@object          # @global_str.1
.Lglobal_str.1:
	.asciz	"\nIs not palindrome..."
	.size	.Lglobal_str.1, 22

	.type	.Lglobal_str.2,@object          # @global_str.2
.Lglobal_str.2:
	.asciz	"\nIs palindrome..."
	.size	.Lglobal_str.2, 18

	.section	".note.GNU-stack","",@progbits
