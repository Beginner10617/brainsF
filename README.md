# Brainf*ck Compiler and Interpreter

This project contains two implementations for the Brainf*ck programming language:

1. A **Brainf*ck interpreter** written in C.
2. A **Brainf*ck compiler** written in C that generates **x86-64 assembly**.

The interpreter was originally written earlier, and the compiler was later added as an experiment in code generation and low-level systems programming.

## Features

- Brainf*ck interpreter implemented in C
- Brainf*ck compiler implemented in C
- Compiler generates **x86-64 assembly**
- Designed for **Linux systems** using **Linux syscalls** for input and output

## Brainf*ck Overview

Brainf*ck is a minimal esoteric programming language with only eight commands:

| Keyword | Description |
|-------|--------|
| `>` | Move data pointer right |
| `<` | Move data pointer left |
| `+` | Increment byte at pointer |
| `-` | Decrement byte at pointer |
| `.` | Output byte at pointer |
| `,` | Read byte into pointer |
| `[` | Jump forward if byte is zero |
| `]` | Jump backward if byte is nonzero |

All other characters are ignored.

## Interpreter

The interpreter executes Brainf*ck programs directly.

Typical behavior:

- Maintains a two tape of memory cells using linked list
- Moves a pointer across the instruction tape after execution of each instruction
- Moves a pointer across the the memory tape executing the current instruction

The interpreter is useful for quickly running Brainf*ck programs without generating assembly.

## Compiler

The compiler translates Brainf*ck source code into **x86-64 assembly**.

### Characteristics

- Generates assembly targeting **Linux x86-64**
- Uses **Linux syscalls** for input and output
- Implements Brainf*ck loops using assembly labels and conditional jumps
- Uses a memory tape allocated on the stack

### Input/Output

The generated assembly uses:

- `syscall 0` for `read`
- `syscall 1` for `write`

Therefore it assumes a **Linux environment**.

## Building

Compile using a C compiler such as `gcc` or `clang`.

### Interpreter
```bash
gcc interpreter.c -o bfi
```
```bash
clang interpreter.c -o bfi
```
### Compiler
```bash
gcc main.c generation.c lexer.c -o bfc
```
```bash
clang main.c generation.c lexer.c -o bfc
```
## Usage
### Interpreter
```bash
./bfi program.bf
```
### Compiler
```bash
./bfc prog.bf -target x86_64 -o prog.s
```
Then assemble and link:
```bash
nasm -f elf64 prog.s
ld prog.o -o prog
```
Run the compiled program:
```bash
./prog
```

# Notes
- The compiler currently targets only x86-64 Linux.
