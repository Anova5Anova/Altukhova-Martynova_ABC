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


