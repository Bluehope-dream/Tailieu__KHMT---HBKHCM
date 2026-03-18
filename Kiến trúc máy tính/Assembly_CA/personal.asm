.data
# Dinh nghia cac bien
seed:        .word 0
float1:      .float 0.25
float2:      .float 0.5
float3:      .float 4.0
floatRandom: .float 32767.0
diem:        .word 0
PI:          .float 0.0

PI_File:     .asciiz "PI.txt"
str1:        .asciiz "So diem nam trong hinh tron: "
str2:        .asciiz "So PI tinh duoc: "
newline:     .asciiz "\n"

# buffer for file write and conversions
buffer:      .space 64
float_buf:   .space 32

.text
.globl main
main:
    # --- Seed random ---
    li $v0,30        # syscall 30 = time
    syscall          # returns time in $v0
    move $a0,$v0
    li $v0,40        # syscall 40 = srand (MARS)
    syscall

    # Khoi tao cac bien
    li $t0,0         # count
    li $t1,50000     # total points
    li $t2,0         # index

loop_start:
    beq $t2,$t1,excit

    # Random x in [0,1]
    li $v0,42
    li $a0,32767
    syscall
    mtc1 $v0,$f0
    cvt.s.w $f0,$f0
    l.s $f1, floatRandom
    div.s $f0,$f0,$f1   # f0 = x

    # Random y in [0,1]
    li $v0,42
    li $a0,32767
    syscall
    mtc1 $v0,$f2
    cvt.s.w $f2,$f2
    l.s $f3, floatRandom
    div.s $f2,$f2,$f3   # f2 = y

    # Check (x-0.5)^2 + (y-0.5)^2 < 0.25
    l.s $f4, float2     # 0.5
    sub.s $f5, $f0, $f4
    sub.s $f6, $f2, $f4
    mul.s $f7, $f5, $f5
    mul.s $f8, $f6, $f6
    add.s $f9, $f7, $f8
    l.s $f10, float1    # 0.25
    c.lt.s $f9, $f10
    bc1f overSkip
    addi $t0,$t0,1
overSkip:
    addi $t2,$t2,1
    j loop_start

excit:
    # Tinh PI = 4 * (count / total)
    mtc1 $t0, $f11
    cvt.s.w $f11, $f11
    mtc1 $t1, $f12
    cvt.s.w $f12, $f12
    div.s $f13, $f11, $f12   # f13 = count/total
    l.s $f14, float3         # 4.0
    mul.s $f15, $f13, $f14   # f15 = PI
    s.s $f15, PI              # store PI to memory

    # --- In ra man hinh ---
    # In so diem
    li $v0,4
    la $a0, str1
    syscall

    li $v0,1
    move $a0, $t0
    syscall

    li $v0,4
    la $a0, newline
    syscall

    # In PI (print float)
    li $v0,4
    la $a0, str2
    syscall

    # Load PI into $f12 safely from memory
    l.s $f12, PI
    li $v0,2
    syscall

    li $v0,4
    la $a0, newline
    syscall

    # --------------------------
    # M? file PI.txt ?? ghi
    # --------------------------
    li $v0,13         # open
    la $a0, PI_File
    li $a1, 1         # write mode
    li $a2, 0
    syscall
    move $s0, $v0     # SAVE file descriptor into $s0 !!!

    # --- Ghi "So diem nam trong hinh tron: " vào file ---
    move $a0, $s0
    li $v0,15         # write file
    la $a1, str1
    li $a2, 29        # number of bytes in str1 (without null)
    syscall

    # --- Chuyen so diem $t0 sang buffer (ASCII) ---
    la $a0, buffer
    jal int_to_ascii_positive   # returns pointer in $v0? (we'll write such that buffer contains string, length in $t7)
    # After return: $t7 = length, buffer filled with ascii digits (no newline)

    # Ghi buffer (so diem)
    move $a0, $s0
    li $v0,15
    la $a1, buffer
    move $a2, $t7     # length
    syscall

    # Ghi newline
    move $a0, $s0
    li $v0,15
    la $a1, newline
    li $a2, 1
    syscall

    # --- Ghi "So PI tinh duoc: " vào file ---
    move $a0, $s0
    li $v0,15
    la $a1, str2
    li $a2, 19
    syscall

    # --- Chuyen float PI sang chuoi string (5 dec places) ---
    la $a0, float_buf
    jal float_to_ascii_5dec   # uses PI memory; returns length in $t7, buffer filled

    # Ghi float_buf
    move $a0, $s0
    li $v0,15
    la $a1, float_buf
    move $a2, $t7
    syscall

    # Ghi newline
    move $a0, $s0
    li $v0,15
    la $a1, newline
    li $a2, 1
    syscall

    # Close file
    move $a0, $s0
    li $v0,16
    syscall

    # Exit
    li $v0,10
    syscall

# -------------------------------
# Routine: int_to_ascii_positive
# Input:
#   $t0 = integer không âm (count)
#   $a0 = ??a ch? buffer ?? ghi chu?i ASCII
# Output:
#   buffer ch?a chu?i ASCII (không có null terminator)
#   $t7 = ?? dài chu?i
# Ghi chú: dùng swap ?? ??o th? t? các ch? s?
# -------------------------------
int_to_ascii_positive:
    addi $sp, $sp, -8
    sw $ra, 4($sp)
    sw $s1, 0($sp)

    move $s1, $a0    # s1 = pointer buffer
    move $t1, $t0    # t1 = copy c?a s?
    li $t7, 0        # t7 = ?? dài

    beq $t1, $zero, ito_zero  # n?u s? = 0, x? lý ??c bi?t

    # --------- Chuy?n s? sang chu?i (ng??c) ----------
    li $t2, 0        # index trong buffer (ng??c)
conv_loop:
    li $t3, 10
    div $t1, $t3
    mfhi $t4           # remainder
    addi $t4, $t4, 48  # chuy?n sang ASCII
    add $t5, $s1, $t2
    sb $t4, 0($t5)
    mflo $t1
    addi $t2, $t2, 1
    bne $t1, $zero, conv_loop

    # --------- ??o chu?i buffer[0..t2-1] ----------
    li $t6, 0          # start index
rev_loop:
    bge $t6, $t2, rev_done
    sub $t3, $t2, $t6
    addi $t3, $t3, -1      # t3 = t2-1-t6

    add $t4, $s1, $t6      # addr1 = buffer + t6
    lb $t5, 0($t4)         # temp1

    add $t6, $s1, $t3      # addr2 = buffer + t3
    lb $t6, 0($t6)          # temp2
    sb $t6, 0($t4)          # buffer[t6] = temp2
    sb $t5, 0($t3)          # buffer[t2-1-t6] = temp1
    addi $t6, $t6, 1
    j rev_loop
rev_done:
    move $t7, $t2
    j ito_end

ito_zero:
    li $t7, 1
    li $t3, '0'
    sb $t3, 0($s1)

ito_end:
    lw $ra, 4($sp)
    lw $s1, 0($sp)
    addi $sp, $sp, 8
    jr $ra
    
# Assumes: PI in label PI (float)
# buffer in $a0
# length returned in $t7

float_to_ascii_5dec:
    addi $sp, $sp, -8
    sw $ra, 4($sp)
    sw $s0, 0($sp)

    move $s0, $a0       # s0 = buffer

    # Load PI
    l.s $f0, PI

    # integer part
    cvt.w.s $f1, $f0
    mfc1 $t0, $f1       # t0 = integer part

    # fractional part
    mtc1 $t0, $f2
    cvt.s.w $f2, $f2
    sub.s $f3, $f0, $f2   # f3 = frac
    # multiply by 100000
    l.s $f4, float100k
    mul.s $f5, $f3, $f4
    cvt.w.s $f6, $f5
    mfc1 $t1, $f6         # t1 = fractional part as integer

    # convert integer part
    move $t2, $t0
    move $a0, $s0
    jal int_to_ascii_positive
    # after return, $t7 = length of integer part
    move $t3, $t7          # save current length

    # append '.'
    add $t4, $s0, $t3
    li $t5, '.'
    sb $t5, 0($t4)
    addi $t3, $t3, 1

    # convert fractional 5 digits
    move $t6, $t1          # fractional integer
    li $t7, 10000
frac_loop:
    beq $t7, 0, frac_done
    divu $t6, $t7
    mflo $t8     # quotient = digit
    mfhi $t6     # remainder
    addi $t8, $t8, 48
    add $t9, $s0, $t3
    sb $t8, 0($t9)
    addi $t3, $t3, 1
    
    	li $t8, 10       # t8 = 10
	divu $t7, $t8    # chia t7 cho 10
	mflo $t7         # quotient
	mfhi $t9         # remainder n?u c?n
    	mflo $t7
    	j frac_loop
frac_done:

    move $t7, $t3    # total length

    lw $ra, 4($sp)
    lw $s0, 0($sp)
    addi $sp, $sp, 8
    jr $ra

.data
float100k: .float 100000.0