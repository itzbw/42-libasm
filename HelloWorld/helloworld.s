section .data
    message db 'Hello, World!', 10    ; 10 is the ASCII code for newline
    message_len equ $ - message

section .text
    global _start

_start:
    ; write(1, message, message_len)
    mov rax, 1          ; system call number for write
    mov rdi, 1          ; file descriptor 1 is stdout
    mov rsi, message    ; address of string to output
    mov rdx, message_len ; number of bytes
    syscall

    ; exit(0)
    mov rax, 60         ; system call number for exit
    xor rdi, rdi        ; exit code 0
    syscall