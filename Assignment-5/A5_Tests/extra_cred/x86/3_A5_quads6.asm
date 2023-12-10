	.section	.rodata
.LC0:
	.string	"4Odd"
.LC1:
	.string	"5Even"
	.text 
	.globl	alph
	.type	alph, @function
alph: 
.LFB7: 
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movq	%rsp, %rbp
	.cfi_def_cfa_register 5
	subq	$42, %rsp
	movq	%rdi, -20(%rbp)
	movl	$2, %eax
	movl	%eax, -24(%rbp)
		movl	-20(%rbp), %eax
	cltd
	idivl 	-24(%rbp)
	movl	%edx, -28(%rbp)
	movl	$0, %eax
	movl	%eax, -32(%rbp)
		movl	-28(%rbp), %eax
	cmpl	-32(%rbp), %eax
	je .L17
	jmp .L18
	jmp .L18
.L17:
		movl	0(%rbp), %eax
	movl	%eax, -33(%rbp)
		movl	-33(%rbp), %eax
	jmp .LFE7
	jmp .L18
.L18:
		movl	0(%rbp), %eax
	movl	%eax, -34(%rbp)
		movl	-34(%rbp), %eax
	jmp .LFE7
	.LFE7: 
leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
	.size	alph, .-alph
	.globl	up
	.type	up, @function
up: 
.LFB8: 
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movq	%rsp, %rbp
	.cfi_def_cfa_register 5
	subq	$28, %rsp
	movq	%rdi, -23(%rbp)
		movl	0(%rbp), %eax
	movl	%eax, -21(%rbp)
		movl	-23(%rbp), %eax
	cmpl	-21(%rbp), %eax
	je .L21
	jmp .L22
	jmp .L22
.L21:
		movl	0(%rbp), %eax
	movl	%eax, -22(%rbp)
		movl	-22(%rbp), %eax
	jmp .LFE8
	jmp .L22
.L22:
		movl	0(%rbp), %eax
	movl	%eax, -23(%rbp)
		movl	-23(%rbp), %eax
	jmp .LFE8
	.LFE8: 
leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
	.size	up, .-up
	.globl	make_string
	.type	make_string, @function
make_string: 
.LFB9: 
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movq	%rsp, %rbp
	.cfi_def_cfa_register 5
	subq	$35, %rsp
	movq	%rdi, -23(%rbp)
		movl	0(%rbp), %eax
	movl	%eax, -21(%rbp)
		movl	-23(%rbp), %eax
	cmpl	-21(%rbp), %eax
	je .L25
	jmp .L26
	jmp .L27
.L25:
	movq 	$.LC0, -29(%rbp)
		movl	-29(%rbp), %eax
	movl	%eax, -25(%rbp)
		movl	-25(%rbp), %eax
	jmp .LFE9
	jmp .L27
.L26:
	movq 	$.LC1, -33(%rbp)
		movl	-33(%rbp), %eax
	movl	%eax, -25(%rbp)
		movl	-25(%rbp), %eax
	jmp .LFE9
.L27:
	.LFE9: 
leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
	.size	make_string, .-make_string
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
	subq	$56, %rsp
	movl	$1319, %eax
	movl	%eax, -25(%rbp)
	movl	-25(%rbp), %eax
	movq	-25(%rbp), %rdi
	call	alph
	movl	%eax, -26(%rbp)
		movl	-26(%rbp), %eax
	movl	%eax, -21(%rbp)
	movl	$1319, %eax
	movl	%eax, -30(%rbp)
	movl	$1, %eax
	movl	%eax, -34(%rbp)
		movl	-30(%rbp), %eax
	movl	-34(%rbp), %edx
	subl 	%edx, %eax
	movl	%eax, -38(%rbp)
	movl	-38(%rbp), %eax
	movq	-38(%rbp), %rdi
	call	alph
	movl	%eax, -39(%rbp)
		movl	-39(%rbp), %eax
	movl	%eax, -21(%rbp)
	movl	-21(%rbp), %eax
	movq	-21(%rbp), %rdi
	call	up
	movl	%eax, -40(%rbp)
		movl	-40(%rbp), %eax
	movl	%eax, -21(%rbp)
	movl	-21(%rbp), %eax
	movq	-21(%rbp), %rdi
	call	make_string
	movl	%eax, -48(%rbp)
		movl	-48(%rbp), %eax
	movl	%eax, -44(%rbp)
	movl	$0, %eax
	movl	%eax, -52(%rbp)
		movl	-52(%rbp), %eax
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
