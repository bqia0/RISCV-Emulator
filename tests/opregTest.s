addi x1, x0, #1
addi x2, x0, #2
add x3, x1, x2
sub x4, x1, x2
and x5, x3, x4
addi x30, x30, #-16
or x6, x30, x3
xor x7, x4, x6
SLT x8, x1, x2
SLT x9, x4, x1
SLTU x10, x1, x2
SLTU x11, x4, x1
SRA x12, x6, x2
SRA x13, x2, x1
SRL x14, x6, x2
SRL x15, x2, x1
SLL x16, x1, x2