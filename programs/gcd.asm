	.text
	.file	"gcd.imm"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	gcd@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.globl	gcd                             # -- Begin function gcd
	.p2align	4, 0x90
	.type	gcd,@function
gcd:                                    # @gcd
	.cfi_startproc
# %bb.0:                                # %gcd_entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$0, 4(%rsp)
	movl	$0, (%rsp)
	movl	$.Lglobal_str, %edi
	callq	writeString@PLT
	callq	readInteger@PLT
	movl	%eax, 4(%rsp)
	callq	readInteger@PLT
	movl	%eax, (%rsp)
	movl	$.Lglobal_str.1, %edi
	callq	writeString@PLT
	movl	4(%rsp), %edi
	movl	(%rsp), %esi
	callq	find_gcd@PLT
	movl	%eax, %edi
	callq	writeInteger@PLT
	movl	$.Lglobal_str.2, %edi
	callq	writeString@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	gcd, .Lfunc_end1-gcd
	.cfi_endproc
                                        # -- End function
	.globl	find_gcd                        # -- Begin function find_gcd
	.p2align	4, 0x90
	.type	find_gcd,@function
find_gcd:                               # @find_gcd
	.cfi_startproc
# %bb.0:                                # %find_gcd_entry
	movl	%edi, -4(%rsp)
	movl	%esi, -8(%rsp)
	movl	$0, -12(%rsp)
	cmpl	%esi, %edi
	jle	.LBB2_2
# %bb.1:                                # %then
	movl	-4(%rsp), %eax
	jmp	.LBB2_3
.LBB2_2:                                # %else
	movl	-8(%rsp), %eax
.LBB2_3:                                # %ifcont
	movl	%eax, -12(%rsp)
	cmpl	$2, -12(%rsp)
	jl	.LBB2_10
	.p2align	4, 0x90
.LBB2_5:                                # %loop
                                        # =>This Inner Loop Header: Depth=1
	movl	-4(%rsp), %eax
	cltd
	idivl	-12(%rsp)
	testl	%edx, %edx
	je	.LBB2_7
# %bb.6:                                #   in Loop: Header=BB2_5 Depth=1
	xorl	%eax, %eax
	testb	%al, %al
	je	.LBB2_9
	jmp	.LBB2_11
	.p2align	4, 0x90
.LBB2_7:                                # %trueBlock
                                        #   in Loop: Header=BB2_5 Depth=1
	movl	-8(%rsp), %eax
	cltd
	idivl	-12(%rsp)
	testl	%edx, %edx
	sete	%al
	testb	%al, %al
	jne	.LBB2_11
.LBB2_9:                                # %else14
                                        #   in Loop: Header=BB2_5 Depth=1
	decl	-12(%rsp)
	cmpl	$2, -12(%rsp)
	jge	.LBB2_5
.LBB2_10:                               # %afterloop
	movl	$1, %eax
	retq
.LBB2_11:                               # %then12
	movl	-12(%rsp), %eax
	retq
.Lfunc_end2:
	.size	find_gcd, .Lfunc_end2-find_gcd
	.cfi_endproc
                                        # -- End function
	.type	.Lglobal_str,@object            # @global_str
	.section	.rodata.str1.1,"aMS",@progbits,1
.Lglobal_str:
	.asciz	"Give me two positive integers: \n"
	.size	.Lglobal_str, 33

	.type	.Lglobal_str.1,@object          # @global_str.1
.Lglobal_str.1:
	.asciz	"\nTheir GCD is: "
	.size	.Lglobal_str.1, 16

	.type	.Lglobal_str.2,@object          # @global_str.2
.Lglobal_str.2:
	.asciz	"\n"
	.size	.Lglobal_str.2, 2

	.section	".note.GNU-stack","",@progbits
