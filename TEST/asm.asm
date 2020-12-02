.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../LP_LIB/Debug/LP_Lib.lib
ExitProcess PROTO : DWORD
EXTRN Concat			: PROC
EXTRN ConvertToChar		: PROC
EXTRN Copy			: PROC
EXTRN ConsoleWrite		: PROC

EXTRN Strlen 			: PROC


.stack 4096
.const
	l0 BYTE 'Арифметические операции', 0
	l1 DWORD 00001488
	l2 DWORD 00000001
	l3 DWORD 00000009
	l4 DWORD 00800000
	l5 DWORD 00000012
	l6 DWORD 00000030
	l7 DWORD 00000000
	l8 DWORD 00000002
	l9 DWORD 00000020
	l10 DWORD 00000004
	l11 DWORD 00000007
	l12 BYTE 'a', 0
	l13 BYTE 'b', 0
	l14 BYTE 'c', 0
	l15 BYTE 'd', 0
	l16 BYTE 'e', 0
	l17 BYTE 'Hello, ', 0
	l18 BYTE 'World!', 0
	l19 BYTE 'Операции со строками', 0
	l20 DWORD 00001010
	l21 DWORD 00000101
	l22 BYTE 'Работа с функциями', 0
	l23 BYTE 'Начало цикла', 0
	l24 BYTE 'Конец цикла', 0
.data
	vhodpupa			DWORD 0
	vhodsuka			DWORD 0
	vhoda			DWORD 0
	vhodb			DWORD 0
	vhodc			DWORD 0
	vhodd			DWORD 0
	vhode			DWORD 0
	vhodsa			DWORD 0
	vhodsb			DWORD 0
	vhodconcatenated			DWORD 0
	vhodx			DWORD 0
	vhody			DWORD 0
	vhodout			DWORD 0
	vhoditerator			DWORD 0

.code
main PROC
	push		offset l0
	pop			vhodsuka

	push		vhodsuka
	call		Strlen
	push		eax
	pop			vhodpupa

	push		vhodpupa
	push		l1
	;\/Вычитание\/
	pop		ebx
	pop		eax
	sub		eax, ebx
	push		eax
	;/\Вычитание/\
	pop			vhoda

	push		vhoda
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		offset l0
	pop			vhodsuka

	push		l2
	push		l3
	;\/Сложение\/
	pop		eax
	pop		ebx
	add		eax, ebx
	push		eax
	;/\Сложение/\
	push		l4
	push		l2
	;\/Сложение\/
	pop		eax
	pop		ebx
	add		eax, ebx
	push		eax
	;/\Сложение/\
	;\/Вычитание\/
	pop		ebx
	pop		eax
	sub		eax, ebx
	push		eax
	;/\Вычитание/\
	pop			vhoda

	push		l5
	push		l6
	;\/Вычитание\/
	pop		ebx
	pop		eax
	sub		eax, ebx
	push		eax
	;/\Вычитание/\
	pop			vhodb

	push		l7
	push		l8
	push		l8
	;\/Умножение\/
	pop		eax
	pop		ebx
	mul		ebx
	push		eax
	;/\Умножение/\
	;\/Вычитание\/
	pop		ebx
	pop		eax
	sub		eax, ebx
	push		eax
	;/\Вычитание/\
	pop			vhodc

	push		l9
	push		l10
	;\/Деление\/
	pop		ebx
	mov		edx, 0
	pop		eax
	div		ebx
	push		eax
	;/\Деление/\
	pop			vhodd

	push		l11
	push		l8
	;\/Остаток от деления\/
	pop		ebx
	mov		edx, 0
	pop		eax
	div		ebx
	push		edx
	;/\Остаток от деления/\
	pop			vhode

	push		offset l12
	call		ConsoleWrite

	push		vhoda
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		offset l13
	call		ConsoleWrite

	push		vhodb
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		offset l14
	call		ConsoleWrite

	push		vhodc
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		offset l15
	call		ConsoleWrite

	push		vhodd
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		offset l16
	call		ConsoleWrite

	push		vhode
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		offset l0
	call		ConsoleWrite

	push		offset l17
	pop			vhodsa

	push		offset l18
	pop			vhodsb

	push		offset l19
	call		ConsoleWrite

	push		vhodsa
	call		ConsoleWrite

	push		vhodsb
	call		ConsoleWrite

	push		vhodconcatenated
	call		ConsoleWrite

	push		offset vhodsb
	push		vhodsa
	call		Copy
	push		vhodsb
	call		ConsoleWrite

	push		offset l19
	call		ConsoleWrite

	push		l20
	pop			vhodx

	push		l21
	pop			vhody

	push		offset l22
	call		ConsoleWrite

	push		vhodout
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		offset l22
	call		ConsoleWrite

	push		l9
	pop			vhoditerator

	push		offset l23
	call		ConsoleWrite

	.while		vhoditerator
	;\/Тело цикла\/
	push		vhoditerator
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	dec			vhoditerator
	;/\Тело цикла/\
	.endw
	push		offset l24
	call		ConsoleWrite

	push		l7
	call		ExitProcess
main ENDP
end main
