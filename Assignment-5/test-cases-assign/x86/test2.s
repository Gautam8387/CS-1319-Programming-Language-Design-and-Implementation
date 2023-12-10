	.text 
	.globl	main
	.type	main, @function
main: 
.LFB0: 
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movq	%rsp, %rbp
	.cfi_def_cfa_register 5
	subq	$28, %rsp
	movl	$0, %eax
	movl	%eax, -24(%rbp)
		movl	-24(%rbp), %eax
	jmp .LFE0
	.LFE0: 
leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
	.size	main, .-main
	.ident	"group-03-julius-stabs-back"
	.section	.note.GNU-stack,"",@progbits
