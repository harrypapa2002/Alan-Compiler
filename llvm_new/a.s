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
	callq	foo@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.globl	foo                             # -- Begin function foo
	.p2align	4, 0x90
	.type	foo,@function
foo:                                    # @foo
	.cfi_startproc
# %bb.0:                                # %foo_entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movabsq	$9691492493780514, %rax         # imm = 0x226E5C6F6F6622
	movq	%rax, (%rsp)
	movq	%rsp, %rdi
	callq	writeString@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	foo, .Lfunc_end1-foo
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
