section .data
	int1	dd 0
	str1	times 100 db 0
	sf	db "%s %d", 0
	pf	db "%s %d", 0x0a


section .text
	global main
	extern printf
	extern scanf
main:
	push rbp
	mov rbp, rsp
	lea rdi, [sf]
	lea rsi, [str1]
	lea rdx, [int1]
	mov rax, 0
	call scanf

	lea rdi, [pf]
	lea rsi, [str1]
	mov rdx, [int1]
	mov rax, 0
	call printf
 
	mov rax, 0
	pop rbp
	ret
