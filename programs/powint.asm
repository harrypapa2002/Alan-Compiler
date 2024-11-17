	.text
	.file	"powint.imm"
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
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$0, 12(%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 20(%rsp)
	movl	$0, 16(%rsp)
	callq	readInteger@PLT
	movl	%eax, 12(%rsp)
	callq	readInteger@PLT
	movl	%eax, 8(%rsp)
	callq	readInteger@PLT
	movl	%eax, 20(%rsp)
	movl	12(%rsp), %edi
	movl	8(%rsp), %esi
	movl	%eax, %edx
	callq	powint@PLT
	movl	%eax, 16(%rsp)
	movl	%eax, %edi
	callq	writeInteger@PLT
	movl	$10, %edi
	callq	writeChar@PLT
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main.1, .Lfunc_end1-main.1
	.cfi_endproc
                                        # -- End function
	.globl	powint                          # -- Begin function powint
	.p2align	4, 0x90
	.type	powint,@function
powint:                                 # @powint
	.cfi_startproc
# %bb.0:                                # %powint_entry
	movl	%edx, %ecx
	movl	%edi, %eax
	movl	%esi, -16(%rsp)
	movl	%edx, -4(%rsp)
	cltd
	idivl	%ecx
	movl	%edx, -8(%rsp)
	movl	$1, -12(%rsp)
	jmp	.LBB2_1
	.p2align	4, 0x90
.LBB2_4:                                # %ifcont
                                        #   in Loop: Header=BB2_1 Depth=1
	movl	-8(%rsp), %eax
	imull	%eax, %eax
	cltd
	idivl	-4(%rsp)
	movl	%edx, -8(%rsp)
	movl	-16(%rsp), %eax
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%eax, %ecx
	sarl	%ecx
	movl	%ecx, -16(%rsp)
.LBB2_1:                                # %cond
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$0, -16(%rsp)
	jle	.LBB2_5
# %bb.2:                                # %loop
                                        #   in Loop: Header=BB2_1 Depth=1
	movl	-16(%rsp), %eax
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%eax, %ecx
	andl	$-2, %ecx
	subl	%ecx, %eax
	cmpl	$1, %eax
	jne	.LBB2_4
# %bb.3:                                # %then
                                        #   in Loop: Header=BB2_1 Depth=1
	movl	-12(%rsp), %eax
	imull	-8(%rsp), %eax
	cltd
	idivl	-4(%rsp)
	movl	%edx, -12(%rsp)
	jmp	.LBB2_4
.LBB2_5:                                # %afterloop
	movl	-12(%rsp), %eax
	retq
.Lfunc_end2:
	.size	powint, .Lfunc_end2-powint
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
