global _start
_start:
    sub rsp, 32768
    mov rbx, rsp
    add byte [rbx], 9
    add rbx, 9
    sub byte [rbx], 9
    mov rax, 60
    mov rdi, 0
    syscall
