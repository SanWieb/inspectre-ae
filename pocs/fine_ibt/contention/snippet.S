.intel_syntax noprefix

.global single_outer
.align 64
single_outer:
    .rept 1
        add eax, 0x1
        .rept 8
            je single_outer
        .endr
    .endr
    jne single_outer
    int3



.global double_outer
.align 64
double_outer:
    .rept 2
        add eax, 0x1
        .rept 8
            je double_outer
        .endr
    .endr
    jne double_outer
    int3
