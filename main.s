global _start
_start:
    sub rsp, 32768
    mov rbx, rsp
    mov al, [rbx]
    cmp al, 0
    je LABEL10
LABEL00:
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    mov al, [rbx]
    cmp al, 0
    je LABEL11
LABEL01:
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    mov al, [rbx]
    cmp al, 0
    jne LABEL01
LABEL11:
    mov rax, 1
    mov rdi, 0
    mov rsi, rbx
    mov rdx, 1
    syscall
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    syscall
    mov rax, 1
    mov rdi, 0
    mov rsi, rbx
    mov rdx, 1
    syscall
    syscall
    syscall
    add byte [rbx], 1
    mov rax, 1
    mov rdi, 0
    mov rsi, rbx
    mov rdx, 1
    syscall
    sub byte [rbx], 1
    mov rax, 1
    mov rdi, 0
    mov rsi, rbx
    mov rdx, 1
    syscall
    mov rax, 1
    mov rdi, 0
    mov rsi, rbx
    mov rdx, 1
    syscall
    mov al, [rbx]
    cmp al, 0
    je LABEL12
LABEL02:
    mov al, [rbx]
    cmp al, 0
    jne LABEL02
LABEL12:
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    syscall
    mov al, [rbx]
    cmp al, 0
    jne LABEL00
LABEL10:
    add byte [rbx], 8
    mov al, [rbx]
    cmp al, 0
    je LABEL13
LABEL03:
    add rbx, 1
    add byte [rbx], 4
    mov al, [rbx]
    cmp al, 0
    je LABEL14
LABEL04:
    add rbx, 1
    add byte [rbx], 2
    add rbx, 1
    add byte [rbx], 3
    add rbx, 1
    add byte [rbx], 3
    add rbx, 1
    add byte [rbx], 1
    sub rbx, 4
    sub byte [rbx], 1
    mov al, [rbx]
    cmp al, 0
    jne LABEL04
LABEL14:
    add rbx, 1
    add byte [rbx], 1
    add rbx, 1
    add byte [rbx], 1
    add rbx, 1
    sub byte [rbx], 1
    add rbx, 2
    add byte [rbx], 1
    mov al, [rbx]
    cmp al, 0
    je LABEL15
LABEL05:
    sub rbx, 1
    mov al, [rbx]
    cmp al, 0
    jne LABEL05
LABEL15:
    sub rbx, 1
    sub byte [rbx], 1
    mov al, [rbx]
    cmp al, 0
    jne LABEL03
LABEL13:
    add rbx, 2
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    add rbx, 1
    sub byte [rbx], 3
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    add byte [rbx], 7
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    syscall
    add byte [rbx], 3
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    add rbx, 2
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    sub rbx, 1
    sub byte [rbx], 1
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    sub rbx, 1
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    add byte [rbx], 3
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    sub byte [rbx], 6
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    sub byte [rbx], 8
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    add rbx, 2
    add byte [rbx], 1
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    add rbx, 1
    add byte [rbx], 2
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    mov rax, 60
    mov rdi, 0
    syscall