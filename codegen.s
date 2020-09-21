.bss
str2:
	.space 13
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
movb $34, str2(, %ebx, 1)
movl $1, %ebx
movb $114, str2(, %ebx, 1)
movl $2, %ebx
movb $101, str2(, %ebx, 1)
movl $3, %ebx
movb $102, str2(, %ebx, 1)
movl $4, %ebx
movb $119, str2(, %ebx, 1)
movl $5, %ebx
movb $114, str2(, %ebx, 1)
movl $6, %ebx
movb $101, str2(, %ebx, 1)
movl $7, %ebx
movb $100, str2(, %ebx, 1)
movl $8, %ebx
movb $113, str2(, %ebx, 1)
movl $9, %ebx
movb $119, str2(, %ebx, 1)
movl $10, %ebx
movb $101, str2(, %ebx, 1)
movl $11, %ebx
movb $102, str2(, %ebx, 1)
movl $12, %ebx
movb $34, str2(, %ebx, 1)
	pushl $str2
	pushl $printfStringFormat
	call printf

	movl $0, %eax
	leave
	ret
