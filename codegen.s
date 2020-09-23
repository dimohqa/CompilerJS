.bss
a:
	.space 4
.data
printf_format:
	.string "%d\n"
printfStringFormat:
	.string "%s\n"
printfCharFormat:
	.string "%c"
.text
.globl main
.type main, @function

main:
	pushl %ebp
	movl %esp, %ebp

	pushl $0
	popl a
	jmp check1
loopStart2:
	pushl a
	pushl $printf_format
	call printf
	pushl a
	pushl $2
	popl %eax
	addl %eax, (%esp)
	popl a
check1:
	pushl a
	pushl $10
	popl %eax
	popl %ebx
	cmpl %eax, %ebx
	jl loopStart2

	movl $0, %eax
	leave
	ret
