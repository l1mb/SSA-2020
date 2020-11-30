.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../LP_LIB/Debug/LP_Lib.lib
ExitProcess PROTO : DWORD
EXTRN Concat		: PROC
EXTRN ConvertToChar		: PROC
EXTRN Copy		: PROC
EXTRN ConsoleWrite		: PROC


.stack 4096
.const
	l0 DWORD 00000001y
	l1 DWORD 00000010y
	l2 DWORD 00000101y
	l3 DWORD 00001010y
	l4 DWORD 00000011y
	l5 BYTE 'Арифметические операции', 0
	l6 BYTE 'Hello, ', 0
	l7 BYTE 'World!', 0
	l8 BYTE 'Операции со строками', 0
	l9 BYTE 'Работа с функциями', 0
	l10 BYTE 'Начало цикла', 0
	l11 BYTE 'Конец цикла', 0
	l12 DWORD 00000000y
.data
	Sumsum			DWORD 0
	Raznsub			DWORD 0
	Multimul			DWORD 0
	Divisiondiv			DWORD 0
	RemOfDivremofdiv			DWORD 0
	maina			DWORD 0
	mainb			DWORD 0
	mainc			DWORD 0
	maind			DWORD 0
	maine			DWORD 0
	mainsa			DWORD 0
	mainsb			DWORD 0
	mainconcatenated			DWORD 0
	mainx			DWORD 0
	mainy			DWORD 0
	mainout			DWORD 0
	mainiterator			DWORD 0

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

Razn PROC b: DWORD, a: DWORD
	push		a
	push		b
	;\/Вычитание\/
	pop		ebx
	pop		eax
	sub		eax, ebx
	push		eax
	;/\Вычитание/\
	pop			Raznsub

	mov		eax, Raznsub
	ret
Razn ENDP

Multi PROC b: DWORD, a: DWORD
	push		a
	push		b
	;\/Умножение\/
	pop		eax
	pop		ebx
	mul		ebx
	push		eax
	;/\Умножение/\
	pop			Multimul

	mov		eax, Multimul
	ret
Multi ENDP

Division PROC b: DWORD, a: DWORD
	push		a
	push		b
	;\/Деление\/
	pop		ebx
	mov		edx, 0
	pop		eax
	div		ebx
	push		eax
	;/\Деление/\
	pop			Divisiondiv

	mov		eax, Divisiondiv
	ret
Division ENDP

RemOfDiv PROC b: DWORD, a: DWORD
	push		a
	push		b
	;\/Остаток от деления\/
	pop		ebx
	mov		edx, 0
	pop		eax
	div		ebx
	push		edx
	;/\Остаток от деления/\
	pop			RemOfDivremofdiv

	mov		eax, RemOfDivremofdiv
	ret
RemOfDiv ENDP

main PROC
	push		l0
	push		l1
	;\/Сложение\/
	pop		eax
	pop		ebx
	add		eax, ebx
	push		eax
	;/\Сложение/\
	push		l1
	push		l0
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
	pop			maina

	push		l1
	push		l0
	;\/Вычитание\/
	pop		ebx
	pop		eax
	sub		eax, ebx
	push		eax
	;/\Вычитание/\
	pop			mainb

	push		l1
	push		l2
	;\/Умножение\/
	pop		eax
	pop		ebx
	mul		ebx
	push		eax
	;/\Умножение/\
	pop			mainc

	push		l3
	push		l1
	;\/Деление\/
	pop		ebx
	mov		edx, 0
	pop		eax
	div		ebx
	push		eax
	;/\Деление/\
	pop			maind

	push		l3
	push		l4
	;\/Остаток от деления\/
	pop		ebx
	mov		edx, 0
	pop		eax
	div		ebx
	push		edx
	;/\Остаток от деления/\
	pop			maine

	push		offset l5
	call		ConsoleWrite

	push		maina
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		mainb
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		mainc
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		maind
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		maine
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		offset l5
	call		ConsoleWrite

	push		offset l6
	pop			mainsa

	push		offset l7
	pop			mainsb

	push		offset l8
	call		ConsoleWrite

	push		mainsa
	call		ConsoleWrite

	push		mainsb
	call		ConsoleWrite

	push		mainsa
	push		mainsb
	call		Concat
	push		eax
	pop			mainconcatenated

	push		mainconcatenated
	call		ConsoleWrite

	push		offset mainsb
	push		mainsa
	call		Copy
	push		mainsb
	call		ConsoleWrite

	push		offset l8
	call		ConsoleWrite

	push		l3
	pop			mainx

	push		l2
	pop			mainy

	push		offset l9
	call		ConsoleWrite

	push		mainx
	push		mainy
	call		Sum
	push		eax
	pop			mainout

	push		mainout
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		mainx
	push		mainy
	call		Razn
	push		eax
	pop			mainout

	push		mainout
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		mainx
	push		mainy
	call		Multi
	push		eax
	pop			mainout

	push		mainout
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		mainx
	push		mainy
	call		Division
	push		eax
	pop			mainout

	push		mainout
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		mainx
	push		mainy
	call		RemOfDiv
	push		eax
	pop			mainout

	push		mainout
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	push		offset l9
	call		ConsoleWrite

	push		l3
	pop			mainiterator

	push		offset l10
	call		ConsoleWrite

	.while		mainiterator
	;\/Тело цикла\/
	push		mainiterator
	call		ConvertToChar
	push		eax
	call		ConsoleWrite

	dec			mainiterator
	;/\Тело цикла/\
	.endw
	push		offset l11
	call		ConsoleWrite

	push		l12
	call		ExitProcess
main ENDP
end main
