global _start

section .data
msg: db 'hello world', 10

section .text
_start:
    mov rax, 1   ; system call number should be stored in rax
    mov rdi, 1   ; argument #1 in rdi: where to write (descriptor)?
    mov rsi, msg ; argument #2 in rsi: where does the string start?
    mov rdx, 12  ; argument #3 in rdx: how many bytes to write?
    syscall      ; this instruction invokes a system call

    mov rax, 60  ; 'exit' syscall number
    xor rdi, rdi ; exit code 0
    syscall      ; this instruction invokes a system call again