	.comm	arr,40,4
	.section	.rodata
.LC0:
	.string	"Element is not present in array"
.LC1:
	.string	"Element is present at index "
.LC2:
	.string	"\n"
	.text 
	.globl	binarySearch
	.type	binarySearch, @function
binarySearch: 
.LFB9: 
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movq	%rsp, %rbp
	.cfi_def_cfa_register 5
	subq	$96, %rsp
	movq	%rdi, -20(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -12(%rbp)
		movl	-16(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jge .L21
	jmp .L26
	jmp .L26
.L21:
		movl	-16(%rbp), %eax
	movl	-20(%rbp), %edx
	subl 	%edx, %eax
	movl	%eax, -28(%rbp)
	movl	$2, %eax
	movl	%eax, -32(%rbp)
		movl	-28(%rbp), %eax
	cltd
	idivl 	-32(%rbp)
	movl	%eax, -36(%rbp)
		movl	-20(%rbp), %eax
	movl	-36(%rbp), %edx
	addl 	%edx, %eax
	movl	%eax, -40(%rbp)
		movl	-40(%rbp), %eax
	movl	%eax, -24(%rbp)
	# =[] operation ; t4 = arr[mid]
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	leaq	0(,%rdx,4), %rdx
	leaq	arr(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, -44(%rbp)
		movl	-44(%rbp), %eax
	cmpl	-12(%rbp), %eax
	je .L22
	jmp .L23
	jmp .L23
.L22:
		movl	-24(%rbp), %eax
	jmp .LFE9
	jmp .L23
.L23:
	# =[] operation ; t5 = arr[mid]
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	leaq	0(,%rdx,4), %rdx
	leaq	arr(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, -48(%rbp)
		movl	-48(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jg .L24
	jmp .L25
	jmp .L25
.L24:
	movl	$1, %eax
	movl	%eax, -52(%rbp)
		movl	-24(%rbp), %eax
	movl	-52(%rbp), %edx
	subl 	%edx, %eax
	movl	%eax, -56(%rbp)
	movl	-20(%rbp), %eax
	movq	-20(%rbp), %rdi
movl	-56(%rbp), %eax
	movq	-56(%rbp), %rsi
movl	-12(%rbp), %eax
	movq	-12(%rbp), %rdx
	call	binarySearch
	movl	%eax, -60(%rbp)
		movl	-60(%rbp), %eax
	jmp .LFE9
	jmp .L25
.L25:
	movl	$1, %eax
	movl	%eax, -64(%rbp)
		movl	-24(%rbp), %eax
	movl	-64(%rbp), %edx
	addl 	%edx, %eax
	movl	%eax, -68(%rbp)
	movl	-68(%rbp), %eax
	movq	-68(%rbp), %rdi
movl	-16(%rbp), %eax
	movq	-16(%rbp), %rsi
movl	-12(%rbp), %eax
	movq	-12(%rbp), %rdx
	call	binarySearch
	movl	%eax, -72(%rbp)
		movl	-72(%rbp), %eax
	jmp .LFE9
	jmp .L26
.L26:
	movl	$1, %eax
	movl	%eax, -76(%rbp)
		movl	-76(%rbp), %eax
	negl	%eax
	movl	%eax, -80(%rbp)
		movl	-80(%rbp), %eax
	jmp .LFE9
	.LFE9: 
leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
	.size	binarySearch, .-binarySearch
	.globl	main
	.type	main, @function
main: 
.LFB10: 
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movq	%rsp, %rbp
	.cfi_def_cfa_register 5
	subq	$140, %rsp
	movl	$5, %eax
	movl	%eax, -28(%rbp)
		movl	-28(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	$0, %eax
	movl	%eax, -32(%rbp)
	movl	$2, %eax
	movl	%eax, -36(%rbp)
	# []= operation ; arr[t15] = t16
	movl	-36(%rbp), %eax
	movl	-32(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	leaq	arr(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	movl	$1, %eax
	movl	%eax, -40(%rbp)
	movl	$3, %eax
	movl	%eax, -44(%rbp)
	# []= operation ; arr[t17] = t18
	movl	-44(%rbp), %eax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	leaq	arr(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	movl	$2, %eax
	movl	%eax, -48(%rbp)
	movl	$4, %eax
	movl	%eax, -52(%rbp)
	# []= operation ; arr[t19] = t20
	movl	-52(%rbp), %eax
	movl	-48(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	leaq	arr(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	movl	$3, %eax
	movl	%eax, -56(%rbp)
	movl	$10, %eax
	movl	%eax, -60(%rbp)
	# []= operation ; arr[t21] = t22
	movl	-60(%rbp), %eax
	movl	-56(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	leaq	arr(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	movl	$4, %eax
	movl	%eax, -64(%rbp)
	movl	$40, %eax
	movl	%eax, -68(%rbp)
	# []= operation ; arr[t23] = t24
	movl	-68(%rbp), %eax
	movl	-64(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	leaq	arr(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	movl	$10, %eax
	movl	%eax, -76(%rbp)
		movl	-76(%rbp), %eax
	movl	%eax, -72(%rbp)
	movl	$0, %eax
	movl	%eax, -84(%rbp)
	movl	$1, %eax
	movl	%eax, -88(%rbp)
		movl	-24(%rbp), %eax
	movl	-88(%rbp), %edx
	subl 	%edx, %eax
	movl	%eax, -92(%rbp)
	movl	-84(%rbp), %eax
	movq	-84(%rbp), %rdi
movl	-92(%rbp), %eax
	movq	-92(%rbp), %rsi
movl	-72(%rbp), %eax
	movq	-72(%rbp), %rdx
	call	binarySearch
	movl	%eax, -96(%rbp)
		movl	-96(%rbp), %eax
	movl	%eax, -80(%rbp)
	movl	$1, %eax
	movl	%eax, -100(%rbp)
		movl	-100(%rbp), %eax
	negl	%eax
	movl	%eax, -104(%rbp)
		movl	-80(%rbp), %eax
	cmpl	-104(%rbp), %eax
	je .L29
	jmp .L30
	jmp .L31
.L29:
	movq 	$.LC0, -108(%rbp)
	movl	-108(%rbp), %eax
	movq	-108(%rbp), %rdi
	call	printStr
	movl	%eax, -112(%rbp)
	jmp .L31
.L30:
	movq 	$.LC1, -116(%rbp)
	movl	-116(%rbp), %eax
	movq	-116(%rbp), %rdi
	call	printStr
	movl	%eax, -120(%rbp)
	movl	-80(%rbp), %eax
	movq	-80(%rbp), %rdi
	call	printInt
	movl	%eax, -124(%rbp)
	movq 	$.LC2, -128(%rbp)
	movl	-128(%rbp), %eax
	movq	-128(%rbp), %rdi
	call	printStr
	movl	%eax, -132(%rbp)
.L31:
	movl	$0, %eax
	movl	%eax, -136(%rbp)
		movl	-136(%rbp), %eax
	jmp .LFE10
	.LFE10: 
leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
	.size	main, .-main
	.ident	"group-03-julius-stabs-back"
	.section	.note.GNU-stack,"",@progbits
