	.text 
	.globl	fact
	.type	fact, @function
fact: 
.LFB6: 
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movq	%rsp, %rbp
	.cfi_def_cfa_register 5
	subq	$52, %rsp
	movq	%rdi, -20(%rbp)
	movl	$0, %eax
	movl	%eax, -24(%rbp)
		movl	-20(%rbp), %eax
	cmpl	-24(%rbp), %eax
	je .L15
	jmp .L16
	jmp .L16
.L15:
	movl	$1, %eax
	movl	%eax, -28(%rbp)
		movl	-28(%rbp), %eax
	jmp .LFE6
	jmp .L16
.L16:
	movl	$1, %eax
	movl	%eax, -32(%rbp)
		movl	-20(%rbp), %eax
	movl	-32(%rbp), %edx
	subl 	%edx, %eax
	movl	%eax, -36(%rbp)
	movl	-36(%rbp), %eax
	movq	-36(%rbp), %rdi
	call	fact
	movl	%eax, -40(%rbp)
		movl	-40(%rbp), %eax
	imull 	-20(%rbp), %eax
	movl	%eax, -44(%rbp)
		movl	-44(%rbp), %eax
	jmp .LFE6
	.LFE6: 
leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
	.size	fact, .-fact
	.globl	choose
	.type	choose, @function
choose: 
.LFB7: 
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movq	%rsp, %rbp
	.cfi_def_cfa_register 5
	subq	$72, %rsp
	movq	%rdi, -20(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$0, %eax
	movl	%eax, -24(%rbp)
		movl	-16(%rbp), %eax
	cmpl	-24(%rbp), %eax
	je .L19
	jmp .L20
	jmp .L20
.L19:
	movl	$1, %eax
	movl	%eax, -28(%rbp)
		movl	-28(%rbp), %eax
	jmp .LFE7
	jmp .L20
.L20:
	movl	$0, %eax
	movl	%eax, -32(%rbp)
		movl	-20(%rbp), %eax
	cmpl	-32(%rbp), %eax
	je .L21
	jmp .L22
	jmp .L22
.L21:
	movl	$0, %eax
	movl	%eax, -36(%rbp)
		movl	-36(%rbp), %eax
	jmp .LFE7
	jmp .L22
.L22:
	movl	-20(%rbp), %eax
	movq	-20(%rbp), %rdi
	call	fact
	movl	%eax, -40(%rbp)
	movl	-16(%rbp), %eax
	movq	-16(%rbp), %rdi
	call	fact
	movl	%eax, -44(%rbp)
		movl	-20(%rbp), %eax
	movl	-16(%rbp), %edx
	subl 	%edx, %eax
	movl	%eax, -48(%rbp)
	movl	-48(%rbp), %eax
	movq	-48(%rbp), %rdi
	call	fact
	movl	%eax, -52(%rbp)
		movl	-44(%rbp), %eax
	imull 	-52(%rbp), %eax
	movl	%eax, -56(%rbp)
		movl	-40(%rbp), %eax
	cltd
	idivl 	-56(%rbp)
	movl	%eax, -60(%rbp)
		movl	-60(%rbp), %eax
	jmp .LFE7
	.LFE7: 
leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
	.size	choose, .-choose
	.globl	main
	.type	main, @function
main: 
.LFB8: 
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movq	%rsp, %rbp
	.cfi_def_cfa_register 5
	subq	$48, %rsp
	movl	$5, %eax
	movl	%eax, -28(%rbp)
		movl	-28(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	$2, %eax
	movl	%eax, -36(%rbp)
		movl	-36(%rbp), %eax
	movl	%eax, -32(%rbp)
	movl	-24(%rbp), %eax
	movq	-24(%rbp), %rdi
movl	-32(%rbp), %eax
	movq	-32(%rbp), %rsi
	call	choose
	movl	%eax, -44(%rbp)
		movl	-44(%rbp), %eax
	movl	%eax, -40(%rbp)
		jmp .LFE8
	.LFE8: 
leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
	.size	main, .-main
	.ident	"group-03-julius-stabs-back"
	.section	.note.GNU-stack,"",@progbits
