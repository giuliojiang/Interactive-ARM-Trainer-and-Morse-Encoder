mov r1,#1
mov r2,#1
cmp r1,r2
beq foo
mov r3,#3
foo:
mov r4,#4
mov r0,#1
mov r1,#5
loop:
mul r2,r1,r0
mov r0,r2
sub r1,r1,#1
cmp r1,#0
bne loop
ldr r0,=0x55555555
ldr r0, =0x42
ldr r0,=0x11111111
mov r3,#0x100
str r2,[r3]