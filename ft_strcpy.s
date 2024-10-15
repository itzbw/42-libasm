section .text
global ft_strcpy

ft_strcpy:
    mov rax, rdi        ; Store the original destination address in rax (for return value)
    
.copy_loop:
    mov cl, [rsi]       ; Load byte from source
    mov [rdi], cl       ; Store byte to destination
    inc rsi             ; Move to next source byte
    inc rdi             ; Move to next destination byte
    test cl, cl         ; Check if we've hit the null terminator
    jnz .copy_loop      ; If not zero, continue the loop
    
    ret                 ; Return, dest is in rax