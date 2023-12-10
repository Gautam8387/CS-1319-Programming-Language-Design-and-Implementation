	.text 
	.globl	main
	.type	main, @function
main: 
.LFB3: 
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movq	%rsp, %rbp
	.cfi_def_cfa_register 5
	subq	$55, %rsp
		movl	0(%rbp), %eax
	movl	%eax, -28(%rbp)
		movl	-28(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	$101, %eax
	movl	%eax, -30(%rbp)
		movl	-30(%rbp), %eax
	movl	%eax, -29(%rbp)
		movl	-24(%rbp), %eax
	movl	%eax, -31(%rbp)
		movl	-29(%rbp), %eax
	movl	%eax, -24(%rbp)
	jmp .L10
.L9:
	movl	$1, %eax
	movl	%eax, -39(%rbp)
		movl	-39(%rbp), %eax
	movl	%eax, -35(%rbp)
	jmp .L11
.L10:
		movl	-24(%rbp), %eax
	cmpl	0(%rbp), %eax
	je .L11
	jmp .L9
.L11:
	movl	$0, %eax
	movl	%eax, -47(%rbp)
		movl	-24(%rbp), %eax
	movl	%eax, -43(%rbp)
	movl	$0, %eax
	movl	%eax, -51(%rbp)
		movl	-51(%rbp), %eax
	jmp .LFE3
	.LFE3: 
leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
	.size	main, .-main
	.ident	"group-03-julius-stabs-back"
	.section	.note.GNU-stack,"",@progbits
