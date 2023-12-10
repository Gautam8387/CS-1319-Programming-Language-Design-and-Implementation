	.text 
	.globl	fun
	.type	fun, @function
fun: 
.LFB2: 
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movq	%rsp, %rbp
	.cfi_def_cfa_register 5
	subq	$48, %rsp
	movq	%rdi, -20(%rbp)
	movl	$0, %eax
	movl	%eax, -24(%rbp)
		movl	-20(%rbp), %eax
	cmpl	-24(%rbp), %eax
	je .L7
	jmp .L8
	jmp .L8
.L7:
		movl	-20(%rbp), %eax
	jmp .LFE2
	jmp .L8
.L8:
	movl	$1, %eax
	movl	%eax, -28(%rbp)
		movl	-20(%rbp), %eax
	movl	-28(%rbp), %edx
	subl 	%edx, %eax
	movl	%eax, -32(%rbp)
	movl	-32(%rbp), %eax
	movq	-32(%rbp), %rdi
	call	fun
	movl	%eax, -36(%rbp)
		movl	-36(%rbp), %eax
	movl	-20(%rbp), %edx
	addl 	%edx, %eax
	movl	%eax, -40(%rbp)
		movl	-40(%rbp), %eax
	jmp .LFE2
	.LFE2: 
leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
	.size	fun, .-fun
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
	subq	$40, %rsp
	movl	$10, %eax
	movl	%eax, -28(%rbp)
		movl	-28(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movq	-24(%rbp), %rdi
	call	fun
	movl	%eax, -32(%rbp)
		movl	-32(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	$0, %eax
	movl	%eax, -36(%rbp)
		movl	-36(%rbp), %eax
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
