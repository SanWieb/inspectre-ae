# Must match with main.c MAX_HISTORY_SIZE !
#define MAX_HISTORY_SIZE 512

.intel_syntax noprefix

.section .text

# ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
# ; fill_bhb
# ; - arg 1 - rdi: ptr to history
# ; - arg 2 - rsi: syscall nr
# ; - arg 3 - rdx: syscall arg1
# ; - arg 4 - rcx: syscall arg2
# ; - arg 5 - rcx: syscall arg3
# ; - arg 6 - rcx: syscall arg4
# ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.global fill_bhb
.align 4096
fill_bhb:

    # Perform 256 conditional branches to fill the BHB
    # rdi points to an array of 256 bytes that dictates the direction of
    # all the 256 branches
    .rept MAX_HISTORY_SIZE
        movzx   rax, BYTE PTR [rdi]
        inc     rdi
        cmp     rax, 1
        je      1f
        1:
    .endr
    mov     rax, rsi
    mov     rdi, rdx
    mov     rsi, rcx
    mov     rdx, r8
    mov     r10, r9
    syscall

    ret

# ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
# ; fill_bhb_fill_regs
# ; - arg 1 - rdi: ptr to history
# ; - arg 2 - rsi: syscall nr
# ; - arg 3 - rdx: syscall argument 1 - 5
# ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.global fill_bhb_fill_regs
.align 4096
fill_bhb_fill_regs:

    # Perform 256 conditional branches to fill the BHB
    # rdi points to an array of 256 bytes that dictates the direction of
    # all the 256 branches
    .rept MAX_HISTORY_SIZE
        movzx   rax, BYTE PTR [rdi]
        inc     rdi
        cmp     rax, 1
        je      1f
        1:
    .endr
    mov     rax, rsi
    mov     rdi, rdx
    mov     rsi, rdx
    mov     r10, rdx
    mov     r8, rdx
    mov     r9, rdx
    syscall
    ret


.global static_fill_bhb_call
.align 4096
static_fill_bhb_call:
    # Perform 256 conditional branches to fill the BHB statically
    # next jmp to the location of the 2th argument
    .rept MAX_HISTORY_SIZE
        mov     rax, 1
        cmp     rax, 1
        je      1f
        1:
    .endr
    mov     rax, rdi
    mov     rdi, rsi
    mov     rsi, rdx
    mov     rdx, rcx
    mov     rcx, r8
    jmp     rax

.global static_fill_bhb_sys
.align 4096
static_fill_bhb_sys:
    # Perform 256 conditional branches to fill the BHB statically
    # next jmp to the location of the 2th argument
    .rept MAX_HISTORY_SIZE
        mov     rax, 1
        cmp     rax, 1
        je      1f
        1:
    .endr
    mov     rax, rdi
    mov     rdi, rsi
    mov     rsi, rdx
    mov     rdx, rcx
    mov     rcx, r8
    syscall
    ret

.global fill_bhb_call
fill_bhb_call:

    # Perform 256 conditional branches to fill the BHB
    # next jmp to the location of the 2th argument
    .rept MAX_HISTORY_SIZE
        movzx   rax, BYTE PTR [rdi]
        inc     rdi
        cmp     rax, 1
        je      1f
        1:
    .endr
    mov     rax, rsi
    mov     rdi, rdx
    mov     rsi, rcx
    mov     rdx, r8
    mov     rcx, r9
    mov     r8, 0
    mov     r9, 0
    jmp     rax



.global fill_bhb_ind_call
fill_bhb_ind_call:

    # Perform 256 conditional branches to fill the BHB
    # next jmp to the location of the 2th argument as a indirect call
    .rept MAX_HISTORY_SIZE
        movzx   rax, BYTE PTR [rdi]
        inc     rdi
        cmp     rax, 1
        je      1f
        1:
    .endr
    mov     rax, rsi
    mov     rdi, rdx
    mov     rsi, rcx
    mov     rdx, r8
    mov     rcx, r9
    jmp     [rax]

