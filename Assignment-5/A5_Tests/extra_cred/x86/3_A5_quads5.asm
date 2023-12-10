	.section	.rodata
.LC0:
	.string	"Hello World!\n"
	.text 
	.globl	newline
	.type	newline, @function
newline: 
.LFB6: 
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movq	%rsp, %rbp
	.cfi_def_cfa_register 5
	subq	$34, %rsp
	movq	%rdi, -23(%rbp)
		movl	0(%rbp), %eax
	movl	%eax, -21(%rbp)
		movl	-23(%rbp), %eax
	cmpl	-21(%rbp), %eax
	je .L15
	jmp .L16
	jmp .L16
.L15:
	movl	$1, %eax
	movl	%eax, -25(%rbp)
		movl	-25(%rbp), %eax
	jmp .LFE6
	jmp .L16
.L16:
	movl	$0, %eax
	movl	%eax, -29(%rbp)
		movl	-29(%rbp), %eax
	jmp .LFE6
	.LFE6: 
leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
	.size	newline, .-newline
	.globl	newline_all
	.type	newline_all, @function
newline_all: 
.LFB7: 
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movq	%rsp, %rbp
	.cfi_def_cfa_register 5
	subq	$52, %rsp
	movq	%rdi, -20(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$0, %eax
	movl	%eax, -28(%rbp)
		movl	-28(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	$0, %eax
	movl	%eax, -32(%rbp)
		movl	-32(%rbp), %eax
	movl	%eax, -24(%rbp)
.L19:
		movl	-24(%rbp), %eax
	cmpl	-16(%rbp), %eax
	jl .L21
	jmp .L22
.L20:
	movl	$1, %eax
	movl	%eax, -36(%rbp)
		movl	-24(%rbp), %eax
	movl	-36(%rbp), %edx
	addl 	%edx, %eax
	movl	%eax, -40(%rbp)
		movl	-40(%rbp), %eax
	movl	%eax, -24(%rbp)
	jmp .L19
.L21:
		movl	0(%rbp), %eax
	movl	%eax, -41(%rbp)
	# []= operation ; s[i] = t7
	movl	-24(%rbp), %eax
	movl	-41(%rbp), %edx
	movl	%edx, -20(%rbp,%rax,4)
	jmp .L20
.L22:
		jmp .LFE7
	.LFE7: 
leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
	.size	newline_all, .-newline_all
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
	subq	$76, %rsp
	movq 	$.LC0, -48(%rbp)
		movl	-48(%rbp), %eax
	movl	%eax, -34(%rbp)
	movl	$13, %eax
	movl	%eax, -56(%rbp)
	# =[] operation ; t10 = s[t9]
	movl	-56(%rbp), %ecx
	movl	-34(%rbp,%rcx,4), %eax
	movl	%eax, -60(%rbp)
	movl	-60(%rbp), %eax
	movq	-60(%rbp), %rdi
	call	newline
	movl	%eax, -64(%rbp)
		movl	-64(%rbp), %eax
	movl	%eax, -52(%rbp)
	movl	$14, %eax
	movl	%eax, -68(%rbp)
	movl	-34(%rbp), %eax
	movq	-34(%rbp), %rdi
movl	-68(%rbp), %eax
	movq	-68(%rbp), %rsi
	call	newline_all
	movl	%eax, 0(%rbp)
	movl	$0, %eax
	movl	%eax, -72(%rbp)
		movl	-72(%rbp), %eax
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
