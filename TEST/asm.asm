.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../LP_LIB/Debug/LP_Lib.lib
ExitProcess PROTO : DWORD
Concat				PROTO:	DWORD,:	DWORD
ConvertToChar		PROTO:	DWORD
Copy				PROTO:	DWORD,:	DWORD
ConsoleWrite		PROTO:	DWORD
Strlen 				PROTO:	DWORD


.stack 4096
.const
	l0	DWORD	00000004
	l1	DWORD	00000003
	l2	DWORD	00000007
	l3	DWORD	00000002
	l4	DWORD	00000008
	l5	BYTE	'Hello, ', 0
	l6	BYTE	'World!', 0
	l7	DWORD	00000000
.data
	Sumsum			DWORD 0
	vhoda			DWORD 0
	vhodb			DWORD 0
	vhodc			DWORD 0
	vhodout			DWORD 0
	vhodsa			DWORD 0
	vhodsb			DWORD 0
	vhodconcatenated			DWORD 0
	vhoditerator			DWORD 0

.code
Sum PROC b: DWORD, a: DWORD
	push		a
	push		b
	;\/Сложение\/
	pop		eax
	pop		ebx
	add		eax, ebx
	push		eax
	;/\Сложение/\
	pop			Sumsum

	mov		eax, Sumsum
	ret
Sum ENDP

main PROC
	push		l0
	push		l1
	;\/Умножение\/
	pop		eax
	pop		ebx
	mul		ebx
	push		eax
	;/\Умножение/\
	pop			vhoda

	push		l2
	push		l3
	;\/Деление\/
	pop		ebx
	mov		edx, 0
	pop		eax
	div		ebx
	push		eax
	;/\Деление/\
	pop			vhodb

	push		l4
	push		l1
	;\/Остаток от деления\/
	pop		ebx
	mov		edx, 0
	pop		eax
	div		ebx
	push		edx
	;/\Остаток от деления/\
	pop			vhodc

	push		vhodb
	push		vhodc
	call		Sum
	push		eax
	pop			vhodout

	push		vhoda
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		vhodb
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		vhodc
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		vhodout
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		offset l5
	pop			vhodsa

	push		offset l6
	pop			vhodsb

	push		vhodsa
	call		Strlen
	push		eax
	pop			vhodout

	push		vhodout
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		vhodsa
	push		vhodsb
	call		Concat
	push		eax
	pop			vhodconcatenated

	push		vhodconcatenated
	call		ConsoleWrite

	push		offset vhodsb
	push		vhodsa
	call		Copy
	push		vhodsb
	call		ConsoleWrite

	push		l2
	pop			vhoditerator

	.while		vhoditerator
	;\/Тело цикла\/
	push		vhoditerator
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	dec			vhoditerator
	;/\Тело цикла/\
	.endw
	push		l7
	call		ExitProcess
main ENDP
end main
