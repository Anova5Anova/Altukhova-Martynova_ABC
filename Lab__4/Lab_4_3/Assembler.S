.data
fmt1: .string "--------------Task 3---------------\n"
fmt2: .string "Result: arg5=%d\n"
.text

.globl main
main:

    lea fmt1(%rip), %rcx
    mov %eax, %edx
    sub $32, %rsp
    call printf
    add $32, %rsp


    mov $1, %ecx
    mov $2, %edx
    mov $3, %r8d
    mov $4, %r9d
    mov $5, %rbp

    push %rbp
    sub $32, %rsp
    call fifth_arg
    add $32, %rsp
    pop %rbp

    lea fmt2(%rip), %rcx
    mov %eax, %edx
    sub $32, %rsp
    call printf
    add $32, %rsp


    xor %eax, %eax
    ret

