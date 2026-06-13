# Ch??ng trình : dãy nguyên
.include "macro.mac"

.data
int_arr: .word 13,57,19,87,63
         .word 14,52,38,63,2025

int_n:   .word 10
int_f:   .word 13

# Thi?t l?p l?nh xu?t f 
xuat_f: .asciiz "a[7]-a[3] = "

################################
# CODE SEGMENT
################################
.text
main:

    la $a1, int_arr

    lw $t0, 28($a1)   # a[7]
    lw $t1, 12($a1)   # a[3]
    subu $t2, $t0, $t1 # a[7] - a[3]
    sw $t2, int_f     # l?u vào int_f
    
    puts_p xuat_f, int_f

Ketthuc:
    li $v0, 10
    syscall
