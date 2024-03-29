.data
a: .double 4.6
b: .double 1.3
s_asm: .string "Assembler: z = %lf\n"
s_cpp: .string "CPP: z = %lf\n"
x: .double 5.657
y: .double 2.359
.text

.globl task6_asm
.globl main

task6_asm:

    sub $16, %rsp

    #define mem_x (%rsp)
    #define mem_y 8(%rsp)
    movq %xmm0, mem_x
    movq %xmm1, mem_y

    // 4.6*x^y-1.3

    fldl mem_y      // �������� y
    fldl mem_x      // �������� x
    fyl2x           // y*log_2(x) <=> log_2(x^y)
    fstpl mem_x     // �������� �������� �� �����

    fld1            // �������� �������
    fldl mem_x      // �������� log_2(x^y)
    fprem           // ��������� ������� ����� log_2(x^y)
    f2xm1           // 2^{log_2(x^y)}-1
    fld1            // �������� �������
    fadd            // 2^{log_2(x^y)}
    fxch            // ������ �� ������� ����� ����� �������
    fldl mem_x      // �������� log_2(x^y)
    fxch            // ������ �� ������� ����� ����� �������
    fscale          // 1*2^[log_2(x^y)]
    fxch            // ������ �� ������� ����� ����� log_2(x^y)
    fstpl mem_x     // �������� x �� �����
    fmul            // 2^[log_2(x^y)]*2^{log_2(x^y)} = 2^(log_2(x^y)) = x^y

    fldl a          // �������� a
    fmul            // a*x^y
    fldl b          // �������� b
    fsubr           // a*x^y-b

    fstpl mem_x
    movq mem_x, %xmm0

    #undef mem_x
    #undef mem_y
    add $16, %rsp
    ret

main:

    sub $8, %rsp

    mov x, %rcx
    mov y, %rdx
    movq %rcx, %xmm0
    movq %rdx, %xmm1

    sub $32, %rsp
    call task6_asm
    add $32, %rsp

    lea s_asm(%rip), %rcx
    movq %xmm0, %rdx
    sub $32, %rsp
    call printf
    add $32, %rsp

    mov x, %rcx
    mov y, %rdx
    movq %rcx, %xmm0
    movq %rdx, %xmm1

    sub $32, %rsp
    call task6_cpp
    add $32, %rsp

    lea s_cpp(%rip), %rcx
    movq %rax, %rdx
    sub $32, %rsp
    call printf
    add $32, %rsp


    add $8, %rsp
    xor %eax, %eax
    ret

