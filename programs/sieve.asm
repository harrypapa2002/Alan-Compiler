	.text
	.file	"sieve.imm"
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
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$112, %rsp
	.cfi_def_cfa_offset 128
	.cfi_offset %rbx, -16
	movl	$0, (%rsp)
	movl	$0, 4(%rsp)
	movq	$0, 12(%rsp)
	movq	$0, 20(%rsp)
	movq	$0, 28(%rsp)
	movq	$0, 36(%rsp)
	movq	$0, 44(%rsp)
	movq	$0, 52(%rsp)
	movq	$0, 60(%rsp)
	movq	$0, 68(%rsp)
	movq	$0, 76(%rsp)
	movq	$0, 84(%rsp)
	movq	$0, 92(%rsp)
	movq	$0, 100(%rsp)
	movl	$0, 108(%rsp)
	movl	$100, 8(%rsp)
	.p2align	4, 0x90
.LBB1_1:                                # %cond
                                        # =>This Inner Loop Header: Depth=1
	movl	(%rsp), %eax
	cmpl	8(%rsp), %eax
	jge	.LBB1_3
# %bb.2:                                # %loop
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$1, %edi
	callq	shrink@PLT
	movslq	(%rsp), %rcx
	movb	%al, 12(%rsp,%rcx)
	incl	(%rsp)
	jmp	.LBB1_1
.LBB1_3:                                # %afterloop
	movl	$2, (%rsp)
	jmp	.LBB1_4
	.p2align	4, 0x90
.LBB1_9:                                # %ifcont
                                        #   in Loop: Header=BB1_4 Depth=1
	incl	(%rsp)
.LBB1_4:                                # %cond2
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_7 Depth 2
	movl	(%rsp), %eax
	imull	%eax, %eax
	cmpl	8(%rsp), %eax
	jg	.LBB1_10
# %bb.5:                                # %loop7
                                        #   in Loop: Header=BB1_4 Depth=1
	movslq	(%rsp), %rbx
	movl	$1, %edi
	callq	shrink@PLT
	cmpb	%al, 12(%rsp,%rbx)
	jne	.LBB1_9
# %bb.6:                                # %then
                                        #   in Loop: Header=BB1_4 Depth=1
	movl	(%rsp), %eax
	imull	%eax, %eax
	movl	%eax, 4(%rsp)
	.p2align	4, 0x90
.LBB1_7:                                # %cond15
                                        #   Parent Loop BB1_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	4(%rsp), %eax
	cmpl	8(%rsp), %eax
	jge	.LBB1_9
# %bb.8:                                # %loop20
                                        #   in Loop: Header=BB1_7 Depth=2
	xorl	%edi, %edi
	callq	shrink@PLT
	movslq	4(%rsp), %rcx
	movb	%al, 12(%rsp,%rcx)
	movl	(%rsp), %eax
	addl	%eax, 4(%rsp)
	jmp	.LBB1_7
.LBB1_10:                               # %afterloop30
	movl	$2, (%rsp)
	jmp	.LBB1_11
	.p2align	4, 0x90
.LBB1_14:                               # %ifcont45
                                        #   in Loop: Header=BB1_11 Depth=1
	incl	(%rsp)
.LBB1_11:                               # %cond31
                                        # =>This Inner Loop Header: Depth=1
	movl	(%rsp), %eax
	cmpl	8(%rsp), %eax
	jge	.LBB1_15
# %bb.12:                               # %loop36
                                        #   in Loop: Header=BB1_11 Depth=1
	movslq	(%rsp), %rbx
	movl	$1, %edi
	callq	shrink@PLT
	cmpb	%al, 12(%rsp,%rbx)
	jne	.LBB1_14
# %bb.13:                               # %then42
                                        #   in Loop: Header=BB1_11 Depth=1
	movl	(%rsp), %edi
	callq	writeInteger@PLT
	movl	$32, %edi
	callq	writeChar@PLT
	jmp	.LBB1_14
.LBB1_15:                               # %afterloop48
	movl	$10, %edi
	callq	writeChar@PLT
	addq	$112, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main.1, .Lfunc_end1-main.1
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
