extern 		__errno_location
extern		malloc
extern		ft_strlen
extern		ft_strcpy

section		.text
global		ft_strdup

ft_strdup:
	push	rdi				; save rdi on the stack

_calculate_len:
	call	ft_strlen		; calculate the length
	mov		rcx, rax		; len is saved in rax and copied into rcx
	inc		rcx				; add one space for \0

_malloc_dest:
	mov		rdi, rcx		; save the required len in rdi
	call	malloc			; call malloc
	cmp		rax, 0			; check if malloc fails
	je		_error			; go to the error routine if it fails

_copy_string:
	mov		rdi, rax		; save the malloced string to rdi
	pop		rsi				; save the original rdi into rsi
	call	ft_strcpy		; call strcpy & result is saved in rax
	ret						; return dst in rax

_error:
	pop		rdi					; clean up stack if malloc fails
	call	__errno_location	; call the errno function
	mov		rdx, 12				; 12 stands for ENOMEM
	mov		[rax], rdx			; save errro code into rax
	mov		rax, 0				; change rax to 0
	ret							; NULL is returned when malloc fails