.globl Complex_func
Complex_func:
.data
fmt: .string "--------------Task 4---------------\nResult: w=(%d,%d)\n"
.text
sub $8, %rsp

mov %edx,%eax
imul %ecx, %edx
imul $2, %edx
add %eax, %ecx
imul %ecx,%ecx
sub %edx, %ecx
add $100,%ecx
add $200,%edx

mov %edx, %r8d
mov %ecx, %edx

lea fmt(%rip), %rcx
sub $32, %rsp
call printf
add $32, %rsp

add $8, %rsp
ret

.globl main
main:

    push %rax
    sub $32, %rsp
    mov $0, %ecx
    mov $0, %edx
    call Complex_func
    add $32, %rsp

    pop %rax
    xor %eax, %eax
    ret

