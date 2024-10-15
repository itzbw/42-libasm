section     .text
global      ft_strcmp
ft_strcmp:
    xor     rcx, rcx        ; Initialize counter to 0
.loop:
    movzx   eax, byte [rdi + rcx]  ; Load byte from s1, zero-extend to 32 bits
    movzx   edx, byte [rsi + rcx]  ; Load byte from s2, zero-extend to 32 bits
    inc     rcx             ; Increment counter
    test    al, al          ; Check if we've reached the end of s1
    jz      .end            ; If so, jump to end
    cmp     al, dl          ; Compare characters
    je      .loop           ; If equal, continue loop
.end:
    sub     eax, edx        ; Compute difference
    ret                     ; Return result in eax
