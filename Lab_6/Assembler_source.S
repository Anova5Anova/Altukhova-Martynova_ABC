.data
s: .string "%d "
task6_term_const: .int 3

.text
.globl task1_asm
.globl task2_asm
.globl task6_term
.globl task6_two_sum
.globl task6_asm



task1_asm:

    sub $8, %rsp
    cmpl $7,%ecx
    setl %al
    add $8, %rsp
    ret


task2_asm:
    sub $8, %rsp
    cmpl $7,%ecx
    movl $23,%eax
    leal 76(%ecx,%ecx,4),%edx
    cmovlel %edx, %eax
    add $8, %rsp
    ret

task6_term:

    sub $16, %rsp
    #define mem_i (%rsp)

    movq %rcx, mem_i
    movq %rcx, %rax

    movq $2, %rcx
    movl $0, %edx
    idiv %rcx

    fldl mem_i
    fldl task6_term_const
    fadd
    fldl task6_term_const
    fdiv

    cmp $0, %edx
    je plus

    fldz
    fsub

    plus:

    fstpl mem_i
    movq mem_i, %xmm0
    #undef mem_i
    add $16, %rsp
    ret


task6_two_sum:

    sub $8, %rsp

    vaddpd %xmm1, %xmm0, %xmm2 // s  = a + b
    vsubpd %xmm0, %xmm2, %xmm3 // bs = s - a
    vsubpd %xmm3, %xmm2, %xmm4 // as = s - sb
    vsubpd %xmm3, %xmm1, %xmm1 // b - bs
    vsubpd %xmm4, %xmm0, %xmm0 // a - as
    vaddpd %xmm1, %xmm0, %xmm3 // (b - bs) + (a - as)
    vaddpd %xmm2, %xmm3, %xmm0 // s = s + (b - bs) + (a - as)

    add $8, %rsp
    ret


task6_asm:

    sub $16, %rsp
    #define eps (%rsp)

    movq %xmm0, eps
    movq %rbx, 8(%rsp)

    movq $0, %rbx  // счетчик

    movq $0, %rcx
    movq %rcx, %xmm0 // i-ое слагаемое
    movq %rcx, %xmm1 // итоговая сумма

    begin_iteration_6:

    movq %rbx, %rcx
    sub $32, %rsp
    call task6_term
    add $32, %rsp

    movq $10000000, %rdx

    vpabsd %xmm0, %xmm2
    movq %xmm2, %rcx
    cmp %rcx, eps
    jge end_loop_6

    // первый параметр функции two_sum - значение суммы, второй - добавляемое слагаемое, поэтмоу необходимо поменять значения местами
    vmovapd %xmm0, %xmm2
    vmovapd %xmm1, %xmm0
    vmovapd %xmm2, %xmm1

    sub $32, %rsp
    call task6_two_sum
    add $32, %rsp

    vmovapd %xmm0, %xmm2
    vmovapd %xmm1, %xmm0
    vmovapd %xmm2, %xmm1

    inc %rbx
    jmp begin_iteration_6

    end_loop_6:

    vmovapd %xmm1, %xmm0

    movq 8(%rsp), %rbx
    #undef eps
    #undef term_i
    add $16, %rsp
    ret
