section .data ; for defining constants and initialized variables
;db stands for "define byte", used to declare a byte-sized (8-bit) data item.
    message db 'Hello, World!', 0Ah    ; 0Ah  = /n

section .text
    global _start   ;function and entry point of our program
    ; visible to the linker, so it can be called from other code

_start: // write (1, "Hello, World!/n", 14)
    mov eax, 4          ; 4 is system call number for write operation 
    mov ebx, 1          ; file descriptor 1 is stdout 
    mov ecx, message    ; address of string to output
    mov edx, 14         ; number of bytes
    int 0x80            ; triggers a software interrupt, which calls the kernel to execute our system call (write in this case)
                        ; int stands for "interrupt" ; When this instruction is executed, the CPU temporarily stops what it's doing and transfers control to the kernel.
    ; The kernel then looks at the value in the eax
    mov eax, 1          ; 1 is system call number for exit
    xor ebx, ebx        ; exit status 0 // XORing a value with itself always results in 0
    int 0x80            ; call kernel


    ;XOR : exclusive OR - sets a bit to 1 if exactly one of two bits is 1, otherwise to 0

; nasm -f elf hello.asm // creates an object file hello.o
; ld -m elf_i386 -o hello hello.o // link it and creates executable file hello
; Executable and Linkable Format
; ld is the GNU linker
; -m elf_i386 specifies the emulation mode (32-bit x86 in this case)

;-elf64 = this is the outflow file format for Linux
;-f = if you don't put the -f to NASM it will choose an outpout file format by itself



; int main() {
    ; const char message[] = "Hello, World!\n";
    ; write(1, message, 14);
    ; return 0;
; }