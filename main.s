.extern _write
.extern _read
.text
.globl _main
_main:
    stp x29, x30, [sp, #-16]!
    mov x29, sp
    sub sp, sp, 32768
    mov x10, sp
    ldrb w0, [x10]
    cmp w0, #0
    b.eq LABEL10
LABEL00:
    mov x0, #1
    mov x1, x10
    mov x2, #1
    bl _write
    ldrb w0, [x10]
    cmp w0, #0
    b.eq LABEL11
LABEL01:
    mov x0, #1
    mov x1, x10
    mov x2, #1
    bl _write
    ldrb w0, [x10]
    cmp w0, #0
    b.ne LABEL01
LABEL11:
    mov x0, #0
    mov x1, x10
    mov x2, #1
    bl _read
    mov x0, #1
    mov x1, x10
    mov x2, #1
    bl _write
    bl _write
    mov x0, #0
    mov x1, x10
    mov x2, #1
    bl _read
    bl _read
    bl _read
    ldrb w0, [x10]
    add w0, w0, #1
    strb w0, [x10]
    mov x0, #0
    mov x1, x10
    mov x2, #1
    bl _read
    ldrb w0, [x10]
    sub w0, w0, #1
    strb w0, [x10]
    mov x0, #0
    mov x1, x10
    mov x2, #1
    bl _read
    mov x0, #0
    mov x1, x10
    mov x2, #1
    bl _read
    ldrb w0, [x10]
    cmp w0, #0
    b.eq LABEL12
LABEL02:
    ldrb w0, [x10]
    cmp w0, #0
    b.ne LABEL02
LABEL12:
    mov x0, #1
    mov x1, x10
    mov x2, #1
    bl _write
    bl _write
    ldrb w0, [x10]
    cmp w0, #0
    b.ne LABEL00
LABEL10:
    ldrb w0, [x10]
    add w0, w0, #8
    strb w0, [x10]
    ldrb w0, [x10]
    cmp w0, #0
    b.eq LABEL13
LABEL03:
    add x10, x10, #1
    ldrb w0, [x10]
    add w0, w0, #4
    strb w0, [x10]
    ldrb w0, [x10]
    cmp w0, #0
    b.eq LABEL14
LABEL04:
    add x10, x10, #1
    ldrb w0, [x10]
    add w0, w0, #2
    strb w0, [x10]
    add x10, x10, #1
    ldrb w0, [x10]
    add w0, w0, #3
    strb w0, [x10]
    add x10, x10, #1
    ldrb w0, [x10]
    add w0, w0, #3
    strb w0, [x10]
    add x10, x10, #1
    ldrb w0, [x10]
    add w0, w0, #1
    strb w0, [x10]
    sub x10, x10, #4
    ldrb w0, [x10]
    sub w0, w0, #1
    strb w0, [x10]
    ldrb w0, [x10]
    cmp w0, #0
    b.ne LABEL04
LABEL14:
    add x10, x10, #1
    ldrb w0, [x10]
    add w0, w0, #1
    strb w0, [x10]
    add x10, x10, #1
    ldrb w0, [x10]
    add w0, w0, #1
    strb w0, [x10]
    add x10, x10, #1
    ldrb w0, [x10]
    sub w0, w0, #1
    strb w0, [x10]
    add x10, x10, #2
    ldrb w0, [x10]
    add w0, w0, #1
    strb w0, [x10]
    ldrb w0, [x10]
    cmp w0, #0
    b.eq LABEL15
LABEL05:
    sub x10, x10, #1
    ldrb w0, [x10]
    cmp w0, #0
    b.ne LABEL05
LABEL15:
    sub x10, x10, #1
    ldrb w0, [x10]
    sub w0, w0, #1
    strb w0, [x10]
    ldrb w0, [x10]
    cmp w0, #0
    b.ne LABEL03
LABEL13:
    add x10, x10, #2
    mov x0, #1
    mov x1, x10
    mov x2, #1
    bl _write
    add x10, x10, #1
    ldrb w0, [x10]
    sub w0, w0, #3
    strb w0, [x10]
    mov x0, #1
    mov x1, x10
    mov x2, #1
    bl _write
    ldrb w0, [x10]
    add w0, w0, #7
    strb w0, [x10]
    mov x0, #1
    mov x1, x10
    mov x2, #1
    bl _write
    bl _write
    ldrb w0, [x10]
    add w0, w0, #3
    strb w0, [x10]
    mov x0, #1
    mov x1, x10
    mov x2, #1
    bl _write
    add x10, x10, #2
    mov x0, #1
    mov x1, x10
    mov x2, #1
    bl _write
    sub x10, x10, #1
    ldrb w0, [x10]
    sub w0, w0, #1
    strb w0, [x10]
    mov x0, #1
    mov x1, x10
    mov x2, #1
    bl _write
    sub x10, x10, #1
    mov x0, #1
    mov x1, x10
    mov x2, #1
    bl _write
    ldrb w0, [x10]
    add w0, w0, #3
    strb w0, [x10]
    mov x0, #1
    mov x1, x10
    mov x2, #1
    bl _write
    ldrb w0, [x10]
    sub w0, w0, #6
    strb w0, [x10]
    mov x0, #1
    mov x1, x10
    mov x2, #1
    bl _write
    ldrb w0, [x10]
    sub w0, w0, #8
    strb w0, [x10]
    mov x0, #1
    mov x1, x10
    mov x2, #1
    bl _write
    add x10, x10, #2
    ldrb w0, [x10]
    add w0, w0, #1
    strb w0, [x10]
    mov x0, #1
    mov x1, x10
    mov x2, #1
    bl _write
    add x10, x10, #1
    ldrb w0, [x10]
    add w0, w0, #2
    strb w0, [x10]
    mov x0, #1
    mov x1, x10
    mov x2, #1
    bl _write
    mov x0, #0
    bl _exit
