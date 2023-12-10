	.text 
	.globl	func
	.type	func, @function
func: 
.LFB0: 
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movq	%rsp, %rbp
	.cfi_def_cfa_register 5
	subq	$28, %rsp
	movq	%rdi, -20(%rbp)
	movq	%rsi, -16(%rbp)
		jmp .LFE0
	.LFE0: 
leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
	.size	func, .-func
	.globl	main
	.type	main, @function
main: 
.LFB1: 
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movq	%rsp, %rbp
	.cfi_def_cfa_register 5
	subq	$92, %rsp
	movl	$1, %eax
	movl	%eax, -28(%rbp)
		movl	-28(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	$1, %eax
	movl	%eax, -32(%rbp)
		movl	-24(%rbp), %eax
	movl	-32(%rbp), %edx
	addl 	%edx, %eax
	movl	%eax, -36(%rbp)
		movl	-36(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	$1, %eax
	movl	%eax, -44(%rbp)
		movl	-44(%rbp), %eax
	movl	-24(%rbp), %edx
	subl 	%edx, %eax
	movl	%eax, -48(%rbp)
		movl	-48(%rbp), %eax
	movl	%eax, -40(%rbp)
	movl	$1, %eax
	movl	%eax, -56(%rbp)
		movl	-56(%rbp), %eax
	cltd
	idivl 	-40(%rbp)
	movl	%eax, -60(%rbp)
		movl	-60(%rbp), %eax
	movl	%eax, -52(%rbp)
	movl	$2, %eax
	movl	%eax, -64(%rbp)
		movl	-52(%rbp), %eax
	imull 	-64(%rbp), %eax
	movl	%eax, -68(%rbp)
	movl	$10, %eax
	movl	%eax, -72(%rbp)
		movl	-68(%rbp), %eax
	movl	-72(%rbp), %edx
	addl 	%edx, %eax
	movl	%eax, -76(%rbp)
		movl	-76(%rbp), %eax
	movl	%eax, -52(%rbp)
	# t11 = *d
	movq	-80(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -84(%rbp)
		movl	-52(%rbp), %eax
	imull 	-52(%rbp), %eax
	movl	%eax, -88(%rbp)
		movl	-88(%rbp), %eax
	cltd
	idivl 	-24(%rbp)
	movl	%edx, -92(%rbp)
	# *d = t13
	movl	-80(%rbp), %eax
	movl	-92(%rbp), %edx
	movl	%edx, (%eax)
		jmp .LFE1
	.LFE1: 
leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
	.size	main, .-main
	.ident	"group-03-julius-stabs-back"
	.section	.note.GNU-stack,"",@progbits
