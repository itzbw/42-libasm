section .text
    global ft_write          ; Declare the function globally
    extern __errno_location  ; For storing errno in the C environment

;RDI: File descriptor (e.g., 1 for stdout)
;RSI: Pointer to the buffer (the message to write)
;RDX: Number of bytes to write

; return value RAX:  either be the number of bytes written or -1

ft_write:
    mov     rax, 1           ; syscall number for write
    syscall                  ; make the syscall

    test    rax, rax         ; test if rax == 0 (no need for cmp, faster)
    js      error            ; jump if rax is negative (error case)
    ret                      ; return rax (success)

error:
; Save the error code before overwriting rax
    mov     rdi, rax         ; Save the error code (negative)
    neg     rdi              ; Make the error code positive (for errno)

    ; Store errno in the appropriate location
    call    __errno_location ; Get the address of errno
    mov     [rax], rdi       ; Store the error code in errno

    ; Return -1 to indicate failure
    mov     rax, -1
    ret
