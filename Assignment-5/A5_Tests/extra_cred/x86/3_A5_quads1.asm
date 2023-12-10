	.section	.rodata
.LC0:
	.string	"Hello World\n"
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
	subq	$52, %rsp
	movq 	$.LC0, -28(%rbp)
	movl	-28(%rbp), %eax
	movq	-28(%rbp), %rdi
	call	printStr
	movl	%eax, -32(%rbp)
		movl	-32(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movq	-24(%rbp), %rdi
	call	printInt
	movl	%eax, -36(%rbp)
		movl	-36(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	$0, %eax
	movl	%eax, -44(%rbp)
	movl	-44(%rbp), %eax
	movq	-44(%rbp), %rdi
	call	readInt
	movl	%eax, -48(%rbp)
		movl	-48(%rbp), %eax
	movl	%eax, -40(%rbp)
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
