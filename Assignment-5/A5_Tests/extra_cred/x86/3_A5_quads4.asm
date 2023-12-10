	.comm	a,12,4
	.section	.rodata
.LC0:
	.string	"Hello World!\n"
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
	subq	$134, %rsp
	movl	$0, %eax
	movl	%eax, -24(%rbp)
	movl	$3, %eax
	movl	%eax, -28(%rbp)
	# []= operation ; a[t0] = t1
	movl	-28(%rbp), %eax
	movl	-24(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	leaq	a(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	movl	$1, %eax
	movl	%eax, -32(%rbp)
	movl	$2, %eax
	movl	%eax, -36(%rbp)
	# []= operation ; a[t2] = t3
	movl	-36(%rbp), %eax
	movl	-32(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	leaq	a(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	movl	$2, %eax
	movl	%eax, -40(%rbp)
	movl	$1, %eax
	movl	%eax, -44(%rbp)
	# []= operation ; a[t4] = t5
	movl	-44(%rbp), %eax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	leaq	a(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	movl	$0, %eax
	movl	%eax, -48(%rbp)
	movl	$0, %eax
	movl	%eax, -52(%rbp)
	# =[] operation ; t8 = a[t7]
	movl	-52(%rbp), %eax
	movslq	%eax, %rdx
	leaq	0(,%rdx,4), %rdx
	leaq	a(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, -56(%rbp)
	movl	$1, %eax
	movl	%eax, -60(%rbp)
		movl	-56(%rbp), %eax
	imull 	a(%rip), %eax
	movl	%eax, -64(%rbp)
	movl	$2, %eax
	movl	%eax, -68(%rbp)
		movl	-64(%rbp), %eax
	imull 	a(%rip), %eax
	movl	%eax, -72(%rbp)
	# []= operation ; a[t6] = t12
	movl	-72(%rbp), %eax
	movl	-48(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	leaq	a(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	movl	$0, %eax
	movl	%eax, -80(%rbp)
	movl	$0, %eax
	movl	%eax, -84(%rbp)
	# =[] operation ; t15 = a[t14]
	movl	-84(%rbp), %eax
	movslq	%eax, %rdx
	leaq	0(,%rdx,4), %rdx
	leaq	a(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, -88(%rbp)
	# []= operation ; b[t13] = t15
	movl	-80(%rbp), %eax
	movl	-88(%rbp), %edx
	movl	%edx, -76(%rbp,%rax,4)
	movq 	$.LC0, -116(%rbp)
		movl	-116(%rbp), %eax
	movl	%eax, -102(%rbp)
	movl	$0, %eax
	movl	%eax, -120(%rbp)
		movl	0(%rbp), %eax
	movl	%eax, -121(%rbp)
	# []= operation ; s[t17] = t18
	movl	-120(%rbp), %eax
	movl	-121(%rbp), %edx
	movl	%edx, -102(%rbp,%rax,4)
	movl	$0, %eax
	movl	%eax, -125(%rbp)
		movl	0(%rbp), %eax
	movl	%eax, -126(%rbp)
	# []= operation ; s[t19] = t20
	movl	-125(%rbp), %eax
	movl	-126(%rbp), %edx
	movl	%edx, -102(%rbp,%rax,4)
	movl	$0, %eax
	movl	%eax, -130(%rbp)
		movl	-130(%rbp), %eax
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
