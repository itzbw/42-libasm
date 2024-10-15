; - ssize_t read(int fd, void *buf, size_t count);

; [Registers]
; rdi -> int fd
; rsi -> void *buf
; rdx -> size_t count
; rax -> return value

extern 		__errno_location	; include external errno

section		.text
global		ft_read

ft_read:
	mov		rax, 0				; 0 is the syscall id for read
	syscall
	test	rax, rax			; set condition codes
	js		_error				; jump if negative (meaning an error occured)
	ret

_error:
	neg		rax					; negate negative rax to positive
	mov		rdx, rax			; save code to rdx to store
	call	__errno_location	; call errno
	mov		[rax], rdx			; save error code to rax
	mov		rax, -1				; set rax to -1 as return value for error case
	ret

;When a system call fails, Linux returns the error code in rax as a negative number (e.g., -EINVAL, -EACCES, etc.). 
;However, in the C library and most programming environments, errno is expected to be a positive number representing the error code (like EINVAL, EACCES, etc.).
;The neg rax instruction negates the negative error number, turning it into a positive value, which is what you want to store in errno.