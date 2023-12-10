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
	subq	$33, %rsp
		movl	0(%rbp), %eax
	movl	%eax, -22(%rbp)
		movl	-22(%rbp), %eax
	movl	%eax, -21(%rbp)
		movl	0(%rbp), %eax
	movl	%eax, -24(%rbp)
		movl	-24(%rbp), %eax
	movl	%eax, -23(%rbp)
		movl	0(%rbp), %eax
	movl	%eax, -26(%rbp)
		movl	-26(%rbp), %eax
	movl	%eax, -25(%rbp)
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
