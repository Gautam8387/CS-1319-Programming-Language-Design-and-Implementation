	.globl	d
	.data
	.align 4
	.type	d, @object
	.size	d, 4
d:
	.long	99
	.globl	t0
	.data
	.align 4
	.type	t0, @object
	.size	t0, 4
t0:
	.long	99
	.text 
	movl	$99, %eax
	movl	%eax, t0(%rip)
		movl	t0(%rip), %eax
	movl	%eax, d(%rip)
	.globl	fun2
	.type	fun2, @function
fun2: 
.LFB3: 
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movq	%rsp, %rbp
	.cfi_def_cfa_register 5
	subq	$36, %rsp
	movq	%rdi, -20(%rbp)
	movl	$0, %eax
	movl	%eax, -28(%rbp)
		movl	-28(%rbp), %eax
	movl	%eax, -24(%rbp)
		movl	-24(%rbp), %eax
	jmp .LFE3
	.LFE3: 
leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
	.size	fun2, .-fun2
	.globl	fun
	.type	fun, @function
fun: 
.LFB4: 
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movq	%rsp, %rbp
	.cfi_def_cfa_register 5
	subq	$56, %rsp
	movq	%rdi, -20(%rbp)
		movl	-20(%rbp), %eax
	cltd
	idivl 	d(%rip)
	movl	%edx, -24(%rbp)
	movl	$0, %eax
	movl	%eax, -28(%rbp)
		movl	-24(%rbp), %eax
	cmpl	-28(%rbp), %eax
	je .L11
	jmp .L12
	jmp .L13
.L11:
	movl	-20(%rbp), %eax
	movq	-20(%rbp), %rdi
	call	fun2
	movl	%eax, -32(%rbp)
	# t5 = *t4
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -36(%rbp)
		movl	-36(%rbp), %eax
	jmp .LFE4
	jmp .L13
.L12:
	movl	$1, %eax
	movl	%eax, -40(%rbp)
		movl	-20(%rbp), %eax
	movl	-40(%rbp), %edx
	addl 	%edx, %eax
	movl	%eax, -44(%rbp)
	movl	-44(%rbp), %eax
	movq	-44(%rbp), %rdi
	call	fun
	movl	%eax, -48(%rbp)
		movl	-48(%rbp), %eax
	jmp .LFE4
.L13:
	.LFE4: 
leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
	.size	fun, .-fun
	.globl	main
	.type	main, @function
main: 
.LFB5: 
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movq	%rsp, %rbp
	.cfi_def_cfa_register 5
	subq	$44, %rsp
	movl	$1, %eax
	movl	%eax, -28(%rbp)
		movl	-28(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movq	-24(%rbp), %rdi
	call	fun
	movl	%eax, -36(%rbp)
		movl	-36(%rbp), %eax
	movl	%eax, -32(%rbp)
	movl	$0, %eax
	movl	%eax, -40(%rbp)
		movl	-40(%rbp), %eax
	jmp .LFE5
	.LFE5: 
leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
	.size	main, .-main
	.ident	"group-03-julius-stabs-back"
	.section	.note.GNU-stack,"",@progbits
