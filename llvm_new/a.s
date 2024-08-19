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
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r14
	pushq	%rbx
	subq	$96, %rsp
	.cfi_offset %rbx, -32
	.cfi_offset %r14, -24
	movl	$65, -32(%rbp)
	movl	$65, -24(%rbp)
	movl	$0, -28(%rbp)
	movl	$0, -20(%rbp)
	movl	$220, %eax
	.p2align	4, 0x90
.LBB1_1:                                # %cond
                                        # =>This Inner Loop Header: Depth=1
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rsp
	movl	$16, -16(%rcx)
	cmpl	$15, -20(%rbp)
	jg	.LBB1_3
# %bb.2:                                # %loop
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rsp
	movl	$137, -16(%rcx)
	imull	$137, -24(%rbp), %ecx
	movq	%rsp, %rdx
	leaq	-16(%rdx), %rsp
	movl	%ecx, -16(%rdx)
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rsp
	movl	$220, -16(%rcx)
	movl	-16(%rdx), %ecx
	addl	%eax, %ecx
	movq	%rsp, %rdx
	leaq	-16(%rdx), %rsp
	movl	%ecx, -16(%rdx)
	addl	-20(%rbp), %ecx
	movq	%rsp, %rdx
	leaq	-16(%rdx), %rsp
	movl	%ecx, -16(%rdx)
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rsp
	movl	$101, -16(%rcx)
	movslq	-16(%rdx), %rcx
	movq	%rsp, %rdx
	leaq	-16(%rdx), %rsp
	imulq	$680390859, %rcx, %rsi          # imm = 0x288DF0CB
	movq	%rsi, %rdi
	shrq	$63, %rdi
	sarq	$36, %rsi
	addl	%edi, %esi
	imull	$101, %esi, %esi
	subl	%esi, %ecx
	movl	%ecx, -16(%rdx)
	movl	%ecx, -24(%rbp)
	movslq	-20(%rbp), %rdx
	movl	%ecx, -96(%rbp,%rdx,4)
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rsp
	movl	$1, -16(%rcx)
	movl	-20(%rbp), %ecx
	movq	%rsp, %rdx
	leaq	-16(%rdx), %rsp
	incl	%ecx
	movl	%ecx, -16(%rdx)
	movl	%ecx, -20(%rbp)
	jmp	.LBB1_1
.LBB1_3:                                # %afterloop
	movq	%rsp, %rax
	leaq	-16(%rax), %rdi
	movq	%rdi, %rsp
	movabsq	$9071492255085153, %r14         # imm = 0x203A7961727261
	movq	%r14, -8(%rax)
	movabsq	$2336349412250971721, %rcx      # imm = 0x206C616974696E49
	movq	%rcx, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$16, -16(%rax)
	leaq	-96(%rbp), %rbx
	movl	$16, %esi
	movq	%rbx, %rdx
	callq	writeArray@PLT
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$16, -16(%rax)
	movl	$16, %edi
	movq	%rbx, %rsi
	callq	bsort@PLT
	movq	%rsp, %rax
	leaq	-16(%rax), %rdi
	movq	%rdi, %rsp
	movq	%r14, -9(%rax)
	movabsq	$6998704207841881939, %rcx      # imm = 0x6120646574726F53
	movq	%rcx, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$16, -16(%rax)
	movl	$16, %esi
	movq	%rbx, %rdx
	callq	writeArray@PLT
	leaq	-16(%rbp), %rsp
	popq	%rbx
	popq	%r14
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end1:
	.size	main.1, .Lfunc_end1-main.1
	.cfi_endproc
                                        # -- End function
	.globl	bsort                           # -- Begin function bsort
	.p2align	4, 0x90
	.type	bsort,@function
bsort:                                  # @bsort
	.cfi_startproc
# %bb.0:                                # %bsort_entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	%edi, -28(%rbp)
	movq	%rsi, -24(%rbp)
	movb	$121, -9(%rbp)
	movb	$121, -1(%rbp)
	.p2align	4, 0x90
.LBB2_1:                                # %cond
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB2_3 Depth 2
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movb	$121, -16(%rax)
	cmpb	$121, -1(%rbp)
	jne	.LBB2_7
# %bb.2:                                # %loop
                                        #   in Loop: Header=BB2_1 Depth=1
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movb	$110, -16(%rax)
	movb	$110, -1(%rbp)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movl	$0, -8(%rbp)
	jmp	.LBB2_3
	.p2align	4, 0x90
.LBB2_6:                                # %ifcont
                                        #   in Loop: Header=BB2_3 Depth=2
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$1, -16(%rax)
	movl	-8(%rbp), %eax
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rsp
	incl	%eax
	movl	%eax, -16(%rcx)
	movl	%eax, -8(%rbp)
.LBB2_3:                                # %cond5
                                        #   Parent Loop BB2_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$1, -16(%rax)
	movl	-28(%rbp), %eax
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rsp
	decl	%eax
	movl	%eax, -16(%rcx)
	cmpl	%eax, -8(%rbp)
	jge	.LBB2_1
# %bb.4:                                # %loop12
                                        #   in Loop: Header=BB2_3 Depth=2
	movslq	-8(%rbp), %rax
	movq	-24(%rbp), %rcx
	movq	%rsp, %rdx
	leaq	-16(%rdx), %rsp
	movl	$1, -16(%rdx)
	movl	-8(%rbp), %edx
	movq	%rsp, %rsi
	leaq	-16(%rsi), %rsp
	incl	%edx
	movl	%edx, -16(%rsi)
	movslq	%edx, %rdx
	movq	-24(%rbp), %rsi
	movl	(%rcx,%rax,4), %eax
	cmpl	(%rsi,%rdx,4), %eax
	jle	.LBB2_6
# %bb.5:                                # %then
                                        #   in Loop: Header=BB2_3 Depth=2
	movslq	-8(%rbp), %rdi
	shlq	$2, %rdi
	addq	-24(%rbp), %rdi
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$1, -16(%rax)
	movl	-8(%rbp), %eax
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rsp
	incl	%eax
	movl	%eax, -16(%rcx)
	movslq	%eax, %rsi
	shlq	$2, %rsi
	addq	-24(%rbp), %rsi
	callq	swap@PLT
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movb	$121, -16(%rax)
	movb	$121, -1(%rbp)
	jmp	.LBB2_6
.LBB2_7:                                # %afterloop39
	movq	%rbp, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end2:
	.size	bsort, .Lfunc_end2-bsort
	.cfi_endproc
                                        # -- End function
	.globl	swap                            # -- Begin function swap
	.p2align	4, 0x90
	.type	swap,@function
swap:                                   # @swap
	.cfi_startproc
# %bb.0:                                # %swap_entry
	movq	%rdi, -8(%rsp)
	movq	%rsi, -16(%rsp)
	movl	(%rdi), %eax
	movl	%eax, -20(%rsp)
	movl	(%rsi), %eax
	movl	%eax, (%rdi)
	movl	-20(%rsp), %eax
	movq	-16(%rsp), %rcx
	movl	%eax, (%rcx)
	retq
.Lfunc_end3:
	.size	swap, .Lfunc_end3-swap
	.cfi_endproc
                                        # -- End function
	.globl	writeArray                      # -- Begin function writeArray
	.p2align	4, 0x90
	.type	writeArray,@function
writeArray:                             # @writeArray
	.cfi_startproc
# %bb.0:                                # %writeArray_entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -32(%rbp)
	movl	%esi, -8(%rbp)
	movq	%rdx, -16(%rbp)
	callq	writeString@PLT
	movl	$0, -20(%rbp)
	movl	$0, -4(%rbp)
	jmp	.LBB4_1
	.p2align	4, 0x90
.LBB4_4:                                # %ifcont
                                        #   in Loop: Header=BB4_1 Depth=1
	movslq	-4(%rbp), %rax
	movq	-16(%rbp), %rcx
	movl	(%rcx,%rax,4), %edi
	callq	writeInteger@PLT
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$1, -16(%rax)
	movl	-4(%rbp), %eax
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rsp
	incl	%eax
	movl	%eax, -16(%rcx)
	movl	%eax, -4(%rbp)
.LBB4_1:                                # %cond
                                        # =>This Inner Loop Header: Depth=1
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jge	.LBB4_5
# %bb.2:                                # %loop
                                        #   in Loop: Header=BB4_1 Depth=1
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	cmpl	$0, -4(%rbp)
	jle	.LBB4_4
# %bb.3:                                # %then
                                        #   in Loop: Header=BB4_1 Depth=1
	movq	%rsp, %rax
	leaq	-16(%rax), %rdi
	movq	%rdi, %rsp
	movb	$0, -14(%rax)
	movw	$8236, -16(%rax)                # imm = 0x202C
	callq	writeString@PLT
	jmp	.LBB4_4
.LBB4_5:                                # %afterloop
	movq	%rsp, %rax
	leaq	-16(%rax), %rdi
	movq	%rdi, %rsp
	movw	$10, -16(%rax)
	callq	writeString@PLT
	movq	%rbp, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end4:
	.size	writeArray, .Lfunc_end4-writeArray
	.cfi_endproc
                                        # -- End function
	.type	.Lglobal_str,@object            # @global_str
	.section	.rodata.str1.1,"aMS",@progbits,1
.Lglobal_str:
	.asciz	", "
	.size	.Lglobal_str, 3

	.type	.Lglobal_str.2,@object          # @global_str.2
.Lglobal_str.2:
	.asciz	"\n"
	.size	.Lglobal_str.2, 2

	.type	.Lglobal_str.3,@object          # @global_str.3
.Lglobal_str.3:
	.asciz	"Initial array: "
	.size	.Lglobal_str.3, 16

	.type	.Lglobal_str.4,@object          # @global_str.4
.Lglobal_str.4:
	.asciz	"Sorted array: "
	.size	.Lglobal_str.4, 15

	.section	".note.GNU-stack","",@progbits
