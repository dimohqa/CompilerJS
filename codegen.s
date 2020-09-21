.bss
num:
	.space 4
.data
printf_format:
	.string "%d\n"
.text
.globl main
.type main, @function

main:
	pushl %ebp
	movl %esp, %ebp

	pushl $6
	popl num
	jmp check
loopStart1:
	pushl num
	pushl $1
	popl %ebx
	popl %eax
	subl %ebx, %eax
	pushl %eax
	popl num
	pushl num
	pushl $printf_format
	call printf
check:
	pushl num
	pushl $0
	popl %eax
	popl %ebx
	cmpl %eax, %ebx
	jne loopStart1

	movl $0, %eax
	leave
	ret
