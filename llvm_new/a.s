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
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$96, %rsp
	movabsq	$9071177945344116, %rax         # imm = 0x203A3033206874
	movq	%rax, -25(%rbp)
	movabsq	$8387794212885654901, %rax      # imm = 0x74676E656C206D75
	movq	%rax, -32(%rbp)
	movabsq	$7883964982526765172, %rax      # imm = 0x6D6978616D206874
	movq	%rax, -40(%rbp)
	movabsq	$7599578524817126004, %rax      # imm = 0x697720676E697274
	movq	%rax, -48(%rbp)
	movabsq	$8295737305385560391, %rax      # imm = 0x7320612065766947
	movq	%rax, -56(%rbp)
	leaq	-56(%rbp), %rdi
	callq	writeString@PLT
	movl	$30, -12(%rbp)
	leaq	-87(%rbp), %rsi
	movl	$30, %edi
	callq	readString@PLT
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	.p2align	4, 0x90
.LBB1_1:                                # %cond
                                        # =>This Inner Loop Header: Depth=1
	movslq	-4(%rbp), %rax
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rsp
	movb	$0, -16(%rcx)
	cmpb	$0, -87(%rbp,%rax)
	je	.LBB1_3
# %bb.2:                                # %loop
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$1, -16(%rax)
	movl	-4(%rbp), %eax
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rsp
	incl	%eax
	movl	%eax, -16(%rcx)
	movl	%eax, -4(%rbp)
	jmp	.LBB1_1
.LBB1_3:                                # %afterloop
	movl	-4(%rbp), %edi
	leaq	-87(%rbp), %rsi
	callq	is_it@PLT
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rsp
	movl	$1, -16(%rcx)
	cmpl	$1, %eax
	jne	.LBB1_5
# %bb.4:                                # %then
	movq	%rsp, %rax
	leaq	-32(%rax), %rdi
	movq	%rdi, %rsp
	movabsq	$2865525648878959, %rcx         # imm = 0xA2E2E2E656D6F
	movq	%rcx, -17(%rax)
	movabsq	$8030591510932906352, %rcx      # imm = 0x6F72646E696C6170
	movq	%rcx, -24(%rax)
	movabsq	$2338616625293641994, %rcx      # imm = 0x20746F6E2073490A
	movq	%rcx, -32(%rax)
	jmp	.LBB1_6
.LBB1_5:                                # %else
	movq	%rsp, %rax
	leaq	-32(%rax), %rdi
	movq	%rdi, %rsp
	movabsq	$3327708695368983662, %rcx      # imm = 0x2E2E656D6F72646E
	movq	%rcx, -24(%rax)
	movabsq	$7596553805675841802, %rcx      # imm = 0x696C61702073490A
	movq	%rcx, -32(%rax)
	movl	$667182, -17(%rax)              # imm = 0xA2E2E
.LBB1_6:                                # %ifcont
	callq	writeString@PLT
	movq	%rbp, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
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
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rsi, -16(%rbp)
	movl	$1, -28(%rbp)
	decl	%edi
	movl	%edi, -24(%rbp)
	movl	%edi, -8(%rbp)
	movl	$0, -20(%rbp)
	movl	$0, -4(%rbp)
	.p2align	4, 0x90
.LBB2_1:                                # %cond
                                        # =>This Inner Loop Header: Depth=1
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$2, -16(%rax)
	movl	-8(%rbp), %eax
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rsp
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%eax, %edx
	sarl	%edx
	movl	%edx, -16(%rcx)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$1, -16(%rax)
	movl	-16(%rcx), %eax
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rsp
	incl	%eax
	movl	%eax, -16(%rcx)
	cmpl	%eax, -4(%rbp)
	jg	.LBB2_6
# %bb.2:                                # %loop
                                        #   in Loop: Header=BB2_1 Depth=1
	movslq	-4(%rbp), %rax
	movq	-16(%rbp), %rcx
	movl	-8(%rbp), %edx
	movq	%rsp, %rsi
	leaq	-16(%rsi), %rsp
	subl	%eax, %edx
	movl	%edx, -16(%rsi)
	movslq	%edx, %rdx
	movq	-16(%rbp), %rsi
	movzbl	(%rcx,%rax), %eax
	cmpb	(%rsi,%rdx), %al
	jne	.LBB2_3
# %bb.5:                                # %else
                                        #   in Loop: Header=BB2_1 Depth=1
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$1, -16(%rax)
	movl	-4(%rbp), %eax
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rsp
	incl	%eax
	movl	%eax, -16(%rcx)
	movl	%eax, -4(%rbp)
	jmp	.LBB2_1
.LBB2_6:                                # %afterloop
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	xorl	%eax, %eax
	jmp	.LBB2_4
.LBB2_3:                                # %then
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$1, -16(%rax)
	movl	$1, %eax
.LBB2_4:                                # %then
	movq	%rbp, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
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
	.asciz	"\nIs not palindrome...\n"
	.size	.Lglobal_str.1, 23

	.type	.Lglobal_str.2,@object          # @global_str.2
.Lglobal_str.2:
	.asciz	"\nIs palindrome...\n"
	.size	.Lglobal_str.2, 19

	.section	".note.GNU-stack","",@progbits
