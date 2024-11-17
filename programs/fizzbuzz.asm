	.text
	.file	"fizzbuzz.imm"
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
	jmp	.LBB1_1
.LBB1_11:                               # %else17
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	4(%rsp), %edi
	callq	writeInteger@PLT
	cmpl	$100, 4(%rsp)
	je	.LBB1_1
	.p2align	4, 0x90
.LBB1_12:                               # %then21
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$32, %edi
	callq	writeChar@PLT
.LBB1_1:                                # %cond
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$99, 4(%rsp)
	jg	.LBB1_13
# %bb.2:                                # %loop
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	4(%rsp), %eax
	incl	%eax
	movl	%eax, 4(%rsp)
	imull	$-1431655765, %eax, %eax        # imm = 0xAAAAAAAB
	addl	$715827882, %eax                # imm = 0x2AAAAAAA
	cmpl	$1431655764, %eax               # imm = 0x55555554
	jbe	.LBB1_6
# %bb.3:                                #   in Loop: Header=BB1_1 Depth=1
	xorl	%eax, %eax
	testb	%al, %al
	je	.LBB1_7
.LBB1_4:                                # %then
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$.Lglobal_str, %edi
	jmp	.LBB1_5
	.p2align	4, 0x90
.LBB1_6:                                # %trueBlock
                                        #   in Loop: Header=BB1_1 Depth=1
	imull	$-858993459, 4(%rsp), %eax      # imm = 0xCCCCCCCD
	addl	$429496729, %eax                # imm = 0x19999999
	cmpl	$858993459, %eax                # imm = 0x33333333
	setb	%al
	testb	%al, %al
	jne	.LBB1_4
.LBB1_7:                                # %else
                                        #   in Loop: Header=BB1_1 Depth=1
	imull	$-1431655765, 4(%rsp), %eax     # imm = 0xAAAAAAAB
	addl	$715827882, %eax                # imm = 0x2AAAAAAA
	cmpl	$1431655764, %eax               # imm = 0x55555554
	ja	.LBB1_9
# %bb.8:                                # %then9
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$.Lglobal_str.2, %edi
	jmp	.LBB1_5
.LBB1_9:                                # %else11
                                        #   in Loop: Header=BB1_1 Depth=1
	imull	$-858993459, 4(%rsp), %eax      # imm = 0xCCCCCCCD
	addl	$429496729, %eax                # imm = 0x19999999
	cmpl	$858993458, %eax                # imm = 0x33333332
	ja	.LBB1_11
# %bb.10:                               # %then15
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$.Lglobal_str.3, %edi
	.p2align	4, 0x90
.LBB1_5:                                # %then
                                        #   in Loop: Header=BB1_1 Depth=1
	callq	writeString@PLT
	cmpl	$100, 4(%rsp)
	jne	.LBB1_12
	jmp	.LBB1_1
.LBB1_13:                               # %afterloop
	movl	$10, %edi
	callq	writeChar@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main.1, .Lfunc_end1-main.1
	.cfi_endproc
                                        # -- End function
	.type	.Lglobal_str,@object            # @global_str
	.section	.rodata.str1.1,"aMS",@progbits,1
.Lglobal_str:
	.asciz	"FizzBuzz"
	.size	.Lglobal_str, 9

	.type	.Lglobal_str.2,@object          # @global_str.2
.Lglobal_str.2:
	.asciz	"Fizz"
	.size	.Lglobal_str.2, 5

	.type	.Lglobal_str.3,@object          # @global_str.3
.Lglobal_str.3:
	.asciz	"Buzz"
	.size	.Lglobal_str.3, 5

	.section	".note.GNU-stack","",@progbits
