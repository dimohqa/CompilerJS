.bss
str2:
	.space 7
.bss
str:
	.space 6
.data
printf_format:
	.string "%d\n"
printfStringFormat:
	.string "%s\n"
.text
.globl main
.type main, @function

main:
	pushl %ebp
	movl %esp, %ebp

movl $0, %ebx
movb $34, str(, %ebx, 1)
movl $1, %ebx
movb $107, str(, %ebx, 1)
movl $2, %ebx
movb $101, str(, %ebx, 1)
movl $3, %ebx
movb $107, str(, %ebx, 1)
movl $4, %ebx
movb $34, str(, %ebx, 1)
movl $0, %ebx
movb $34, str2(, %ebx, 1)
movl $1, %ebx
movb $119, str2(, %ebx, 1)
movl $2, %ebx
movb $97, str2(, %ebx, 1)
movl $3, %ebx
movb $105, str2(, %ebx, 1)
movl $4, %ebx
movb $116, str2(, %ebx, 1)
movl $5, %ebx
movb $34, str2(, %ebx, 1)
	pushl $str
	pushl $printfStringFormat
	call printf

	movl $0, %eax
	leave
	ret
