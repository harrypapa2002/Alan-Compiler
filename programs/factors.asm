	.text
	.file	"factors.imm"
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
	movl	$0, 16(%rsp)
	movl	$0, 12(%rsp)
	movl	$0, 20(%rsp)
	movl	$.Lglobal_str, %edi
	callq	writeString@PLT
	callq	readInteger@PLT
	movl	%eax, 16(%rsp)
	movl	$2, 12(%rsp)
	movl	$1, 20(%rsp)
	jmp	.LBB1_1
	.p2align	4, 0x90
.LBB1_5:                                # %ifcont
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$0, 20(%rsp)
	movl	12(%rsp), %edi
	callq	writeInteger@PLT
	movl	$10, %edi
	callq	writeChar@PLT
.LBB1_6:                                # %ifcont8
                                        #   in Loop: Header=BB1_1 Depth=1
	incl	12(%rsp)
.LBB1_1:                                # %cond
                                        # =>This Inner Loop Header: Depth=1
	movl	16(%rsp), %eax
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%eax, %ecx
	sarl	%ecx
	cmpl	%ecx, 12(%rsp)
	jg	.LBB1_7
# %bb.2:                                # %loop
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	16(%rsp), %eax
	cltd
	idivl	12(%rsp)
	testl	%edx, %edx
	jne	.LBB1_6
# %bb.3:                                # %then
                                        #   in Loop: Header=BB1_1 Depth=1
	cmpl	$0, 20(%rsp)
	je	.LBB1_5
# %bb.4:                                # %then4
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$.Lglobal_str.2, %edi
	callq	writeString@PLT
	movl	16(%rsp), %edi
	callq	writeInteger@PLT
	movl	$.Lglobal_str.3, %edi
	callq	writeString@PLT
	jmp	.LBB1_5
.LBB1_7:                                # %afterloop
	cmpl	$0, 20(%rsp)
	je	.LBB1_9
# %bb.8:                                # %then12
	movl	16(%rsp), %edi
	callq	writeInteger@PLT
	movl	$.Lglobal_str.4, %edi
	callq	writeString@PLT
.LBB1_9:                                # %ifcont16
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main.1, .Lfunc_end1-main.1
	.cfi_endproc
                                        # -- End function
	.type	.Lglobal_str,@object            # @global_str
	.section	.rodata.str1.1,"aMS",@progbits,1
.Lglobal_str:
	.asciz	"Please, give me a positive integer: "
	.size	.Lglobal_str, 37

	.type	.Lglobal_str.2,@object          # @global_str.2
.Lglobal_str.2:
	.asciz	"The non-trivial factors of "
	.size	.Lglobal_str.2, 28

	.type	.Lglobal_str.3,@object          # @global_str.3
.Lglobal_str.3:
	.asciz	" are: \n"
	.size	.Lglobal_str.3, 8

	.type	.Lglobal_str.4,@object          # @global_str.4
.Lglobal_str.4:
	.asciz	" is prime\n"
	.size	.Lglobal_str.4, 11

	.section	".note.GNU-stack","",@progbits
