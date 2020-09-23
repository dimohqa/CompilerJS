.bss
b:
	.space 4
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

	pushl $2
	popl a
	pushl $2
	popl b
	jmp check
loopStart1:
	pushl b
	pushl b
	popl %eax
	popl %ebx
	imull %ebx
	pushl %eax
	popl b
	pushl b
	pushl $printf_format
	call printf
	pushl a
	pushl $1
	popl %eax
	addl %eax, (%esp)
	popl a
	pushl a
	pushl $2
	popl %eax
	popl %ebx
	cmpl %eax, %ebx
	jg greater1
jmp next1
greater1:
	pushl $34
	pushl $printfCharFormat
	call printf
	pushl $108
	pushl $printfCharFormat
	call printf
	pushl $101
	pushl $printfCharFormat
	call printf
	pushl $108
	pushl $printfCharFormat
	call printf
	pushl $34
	pushl $printfCharFormat
	call printf
	pushl $10
	pushl $printfCharFormat
	call printf
	pushl a
	pushl $4
	popl %eax
	popl %ebx
	cmpl %eax, %ebx
	jl less1
jmp next1
less1:
	pushl $34
	pushl $printfCharFormat
	call printf
	pushl $107
	pushl $printfCharFormat
	call printf
	pushl $101
	pushl $printfCharFormat
	call printf
	pushl $107
	pushl $printfCharFormat
	call printf
	pushl $34
	pushl $printfCharFormat
	call printf
	pushl $10
	pushl $printfCharFormat
	call printf
next1:
next2:
check:
	pushl a
	pushl $3
	pushl $3
	popl %eax
	addl %eax, (%esp)
	popl %eax
	popl %ebx
	cmpl %eax, %ebx
	jl loopStart1

	movl $0, %eax
	leave
	ret
