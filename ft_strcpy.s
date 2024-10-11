section .text
global ft_strcpy

;rdi contains the first argument (dest)
;rsi contains the second argument (src)

ft_strcpy:
    push rdi            ; Save the original destination address, because we need to return it at the end
    xor rcx, rcx        ; Initialize counter to 0

copy_loop:
    mov al, [rsi + rcx] ; Load byte from source
    mov [rdi + rcx], al ; Store byte to destination
    test al, al         ; Check if we've hit the null terminator
    jz end_copy         ; If zero, end the copy
    inc rcx             ; Move to next character
    jmp copy_loop       ; Continue the loop

end_copy:
    pop rax             ; Retrieve the original destination address (return value)
    ret                 ; Return, dest is in rax