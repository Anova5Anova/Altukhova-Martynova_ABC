.data
fmt: .string "--------------Task 2---------------\nResult: z=%d\n"
.text

.globl foo
foo:
sub $8, %rsp
mov %edx, %eax
imul $5,%eax
not %eax
inc %eax
add %ecx, %eax
add $1234,%eax
add $8, %rsp
ret

.globl main
main:

sub $32, %rsp
mov $1, %ecx
mov $0, %edx
call foo
add $32, %rsp


lea fmt(%rip), %rcx
mov %eax, %edx
sub $32, %rsp
call printf
add $32, %rsp

xor %eax, %eax
ret
