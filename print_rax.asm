section .data
codes:
    db '0123456789ABCDEF'

section .text
global _start

_start:
    mov rax, 0x1122334455667788 ; number 1122... in hexadecimal format, store this value address
    ; rax can hold: 1) system call number 2) values for calculation
    mov rdi, 1  ; where to write (descriptor) 1: terminal console 
    mov rdx, 1  ; how many bytes to write (8-bit)
    mov rcx, 64 ; the number of loop 

    ; Each 4 bits should be output as one hexadecimal digit
    ; Use shift and bitwise AND to isolate them
    ; the result is the offset in 'codes' array

.loop_start:
    push rax   ; push the rax onto the stack, decrease the stack pointer (rsp)
    sub rcx, 4 ; each loop will cost 4, thus there are only 64 / 4 = 16 loops = 16 digits (each digit 4 bits)
    ; cl is a register, smallest part of rcx
    ; rax -- eax -- ax -- ah + al 
    ; rcx -- ecx -- cx -- ch + cl

    sar rax, cl
    and rax, 0xf ; 4 bits (1111)

    lea rsi, [codes + rax] ; load effective address instruction into registers
    ; lea compute the address of [code + rax] where rax is the 4-bit offset and stror that address in rsi register
    mov rax, 1 ; system call number should be stored in rax => write

    push rcx ; push to stack to save this current value
    syscall ; syscall leaves rcx and r11 changed => write value

    pop rcx ; recover the rcx value by poping stack
    pop rax ; recover the rax value by poping stack

    ; test can be used for the fatest 'is it a zero?' check
    ; see docs for 'test' command
    test rcx, rcx
    jnz .loop_start ; continue the loop unitl rcx becomes 0