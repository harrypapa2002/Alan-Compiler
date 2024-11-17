	.text
	.file	"primes.imm"
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
	movl	$0, 20(%rsp)
	movl	$0, 12(%rsp)
	movl	$0, 16(%rsp)
	movl	$.Lglobal_str, %edi
	callq	writeString@PLT
	callq	readInteger@PLT
	movl	%eax, 20(%rsp)
	movl	$.Lglobal_str.2, %edi
	callq	writeString@PLT
	movl	20(%rsp), %edi
	callq	writeInteger@PLT
	movl	$.Lglobal_str.3, %edi
	callq	writeString@PLT
	movl	$0, 16(%rsp)
	cmpl	$2, 20(%rsp)
	jl	.LBB1_2
# %bb.1:                                # %then
	incl	16(%rsp)
	movl	$2, %edi
	callq	writeInteger@PLT
	movl	$.Lglobal_str.4, %edi
	callq	writeString@PLT
.LBB1_2:                                # %ifcont
	cmpl	$3, 20(%rsp)
	jl	.LBB1_4
# %bb.3:                                # %then4
	incl	16(%rsp)
	movl	$3, %edi
	callq	writeInteger@PLT
	movl	$.Lglobal_str.5, %edi
	callq	writeString@PLT
.LBB1_4:                                # %ifcont9
	movl	$6, 12(%rsp)
	jmp	.LBB1_5
	.p2align	4, 0x90
.LBB1_13:                               # %ifcont33
                                        #   in Loop: Header=BB1_5 Depth=1
	addl	$6, 12(%rsp)
.LBB1_5:                                # %cond
                                        # =>This Inner Loop Header: Depth=1
	movl	12(%rsp), %eax
	cmpl	20(%rsp), %eax
	jg	.LBB1_14
# %bb.6:                                # %loop
                                        #   in Loop: Header=BB1_5 Depth=1
	movl	12(%rsp), %edi
	decl	%edi
	callq	prime@PLT
	cmpl	$1, %eax
	jne	.LBB1_8
# %bb.7:                                # %then12
                                        #   in Loop: Header=BB1_5 Depth=1
	incl	16(%rsp)
	movl	12(%rsp), %edi
	decl	%edi
	callq	writeInteger@PLT
	movl	$.Lglobal_str.6, %edi
	callq	writeString@PLT
.LBB1_8:                                # %ifcont19
                                        #   in Loop: Header=BB1_5 Depth=1
	movl	12(%rsp), %eax
	cmpl	20(%rsp), %eax
	je	.LBB1_9
# %bb.10:                               # %trueBlock
                                        #   in Loop: Header=BB1_5 Depth=1
	movl	12(%rsp), %edi
	incl	%edi
	callq	prime@PLT
	cmpl	$1, %eax
	sete	%al
	testb	%al, %al
	jne	.LBB1_12
	jmp	.LBB1_13
	.p2align	4, 0x90
.LBB1_9:                                #   in Loop: Header=BB1_5 Depth=1
	xorl	%eax, %eax
	testb	%al, %al
	je	.LBB1_13
.LBB1_12:                               # %then26
                                        #   in Loop: Header=BB1_5 Depth=1
	incl	16(%rsp)
	movl	12(%rsp), %edi
	incl	%edi
	callq	writeInteger@PLT
	movl	$.Lglobal_str.7, %edi
	callq	writeString@PLT
	jmp	.LBB1_13
.LBB1_14:                               # %afterloop
	movl	$.Lglobal_str.8, %edi
	callq	writeString@PLT
	movl	16(%rsp), %edi
	callq	writeInteger@PLT
	movl	$.Lglobal_str.9, %edi
	callq	writeString@PLT
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main.1, .Lfunc_end1-main.1
	.cfi_endproc
                                        # -- End function
	.globl	prime                           # -- Begin function prime
	.p2align	4, 0x90
	.type	prime,@function
prime:                                  # @prime
	.cfi_startproc
# %bb.0:                                # %prime_entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	%edi, (%rsp)
	movl	$0, 4(%rsp)
	testl	%edi, %edi
	jns	.LBB2_1
# %bb.8:                                # %then
	xorl	%edi, %edi
	subl	(%rsp), %edi
	callq	prime@PLT
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.LBB2_1:                                # %else
	.cfi_def_cfa_offset 16
	cmpl	$1, (%rsp)
	jg	.LBB2_2
.LBB2_9:                                # %then4
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.LBB2_2:                                # %else6
	.cfi_def_cfa_offset 16
	cmpl	$2, (%rsp)
	jne	.LBB2_3
.LBB2_10:                               # %then8
	movl	$1, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.LBB2_3:                                # %else10
	.cfi_def_cfa_offset 16
	movl	(%rsp), %eax
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%eax, %ecx
	andl	$-2, %ecx
	cmpl	%ecx, %eax
	je	.LBB2_9
# %bb.4:                                # %else15
	movl	$3, 4(%rsp)
	.p2align	4, 0x90
.LBB2_5:                                # %cond
                                        # =>This Inner Loop Header: Depth=1
	movl	(%rsp), %eax
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%eax, %ecx
	sarl	%ecx
	cmpl	%ecx, 4(%rsp)
	jg	.LBB2_10
# %bb.6:                                # %loop
                                        #   in Loop: Header=BB2_5 Depth=1
	movl	(%rsp), %eax
	cltd
	idivl	4(%rsp)
	testl	%edx, %edx
	je	.LBB2_9
# %bb.7:                                # %else23
                                        #   in Loop: Header=BB2_5 Depth=1
	addl	$2, 4(%rsp)
	jmp	.LBB2_5
.Lfunc_end2:
	.size	prime, .Lfunc_end2-prime
	.cfi_endproc
                                        # -- End function
	.type	.Lglobal_str,@object            # @global_str
	.section	.rodata.str1.1,"aMS",@progbits,1
.Lglobal_str:
	.asciz	"Please, give me the upper limit: "
	.size	.Lglobal_str, 34

	.type	.Lglobal_str.2,@object          # @global_str.2
.Lglobal_str.2:
	.asciz	"Prime numbers between 0 and "
	.size	.Lglobal_str.2, 29

	.type	.Lglobal_str.3,@object          # @global_str.3
.Lglobal_str.3:
	.asciz	":\n\n"
	.size	.Lglobal_str.3, 4

	.type	.Lglobal_str.4,@object          # @global_str.4
.Lglobal_str.4:
	.asciz	"\n"
	.size	.Lglobal_str.4, 2

	.type	.Lglobal_str.5,@object          # @global_str.5
.Lglobal_str.5:
	.asciz	"\n"
	.size	.Lglobal_str.5, 2

	.type	.Lglobal_str.6,@object          # @global_str.6
.Lglobal_str.6:
	.asciz	"\n"
	.size	.Lglobal_str.6, 2

	.type	.Lglobal_str.7,@object          # @global_str.7
.Lglobal_str.7:
	.asciz	"\n"
	.size	.Lglobal_str.7, 2

	.type	.Lglobal_str.8,@object          # @global_str.8
.Lglobal_str.8:
	.asciz	"\n"
	.size	.Lglobal_str.8, 2

	.type	.Lglobal_str.9,@object          # @global_str.9
.Lglobal_str.9:
	.asciz	" prime number(s) were found.\n"
	.size	.Lglobal_str.9, 30

	.section	".note.GNU-stack","",@progbits
