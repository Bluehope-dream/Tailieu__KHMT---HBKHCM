# ===============================
# int_to_string: chuy?n s? nguyên sang chu?i ASCII
# Input: $a0 = integer, $a1 = ??a ch? buffer
# Output: buffer ch?a chu?i ASCII + null-terminate
# Clobbers: $t0-$t5
# ===============================
int_to_string:
    move $t0, $a0          # t0 = s? nguyên
    move $t1, $a1          # t1 = con tr? ghi t?m
    li   $t2, 10           # chia 10
    li   $t3, 0            # ??m ch? s?

    beq  $t0, $zero, write_zero_int

convert_loop:
    div  $t0, $t2
    mfhi $t4               # l?y ph?n d?
    addi $t4, $t4, 48      # chuy?n sang ASCII
    sb   $t4, 0($t1)       # ghi vào buffer t?m
    addi $t1, $t1, 1
    mflo $t0
    addi $t3, $t3, 1
    bnez $t0, convert_loop

# --- ??o chu?i t? t?m sang buffer g?c ---
    move $t5, $a1          # t5 = con tr? ghi vào buffer
reverse_loop:
    addi $t1, $t1, -1
    lb   $t4, 0($t1)
    sb   $t4, 0($t5)
    addi $t5, $t5, 1
    addi $t3, $t3, -1
    bgtz $t3, reverse_loop

    sb $zero, 0($t5)       # null-terminate
    jr $ra

write_zero_int:
    li $t4, 48           # '0'
    move $t1, $a1        # dùng t1 làm con tr?
    sb $t4, 0($t1)
    addi $t1, $t1, 1
    sb $zero, 0($t1)     # null terminate
    jr $ra

# ===============================
# float_to_string: chuy?n float sang chu?i ASCII 5 ch? s? th?p phân
# Input: $f12 = float, $a1 = ??a ch? buffer
# Output: buffer ch?a chu?i d?ng "x.yyyyy"
# Clobbers: $f0-$f2, $t0-$t6
# ===============================
	.data
float_100000: .float 100000.0
float_to_string:
    # --- L?y ph?n nguyên ---
    cvt.w.s $f0, $f12
    mfc1 $t0, $f0            # t0 = ph?n nguyên
    move $a0, $t0
    move $a2, $a1             # a2 gi? start c?a buffer
    jal int_to_string         # ghi ph?n nguyên vào buffer

    # --- Thêm d?u '.' ---
    move $t1, $a2             # t1 tìm end ph?n nguyên
find_end_int:
    lb $t2, 0($t1)
    beq $t2, $zero, add_dot
    addi $t1, $t1, 1
    j find_end_int

add_dot:
    li $t2, 46                # ASCII '.'
    sb $t2, 0($t1)
    addi $t1, $t1, 1

    # --- L?y ph?n th?p phân 5 ch? s? ---
    l.s  $f1, float_100000    # f1 = 100000.0
    mul.s $f2, $f12, $f1
    cvt.w.s $f2, $f2
    mfc1 $t3, $f2             # t3 = ph?n th?p phân 5 ch? s?

    # --- Thêm 0 ??u n?u thi?u ---
    li $t4, 10000
    blt $t3, $t4, pad_zero
    j convert_frac

pad_zero:
    li $t5, 5
    move $t6, $t3
count_digits:
    beq  $t6, $zero, pad_done
    div  $t6, $t6, 10
    mflo $t6
    addi $t5, $t5, -1
    bgtz $t6, count_digits

pad_done:
pad_loop:
    beq  $t5, $zero, convert_frac
    li   $t2, 48
    sb   $t2, 0($t1)
    addi $t1, $t1, 1
    addi $t5, $t5, -1
    j pad_loop

convert_frac:
    move $a0, $t3
    move $a1, $t1
    jal int_to_string

    # --- Null-terminate ---
    move $t1, $a1
find_end_frac:
    lb $t2, 0($t1)
    beq $t2, $zero, done_float
    addi $t1, $t1, 1
    j find_end_frac

done_float:
    sb $zero, 0($t1)
    jr $ra
