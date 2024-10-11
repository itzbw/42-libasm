section .text
global ft_strlen

ft_strlen:
    xor rax, rax        ; Initialize counter to 0

count_loop:
    cmp byte [rdi], 0   ; Check if current character is null terminator // In 64-bit calling convention (System V AMD64 ABI), the first argument is passed in rdi
    je end_count        ; If zero, end the loop // to jump if equal
    inc rax             ; Increment the counter
    inc rdi             ; Move to the next character
    jmp count_loop      ; Continue the loop // jmp unconditionally

end_count:
    ret                 ; Return, length is in rax


    ;  Intel syntax as required (destination operand first)