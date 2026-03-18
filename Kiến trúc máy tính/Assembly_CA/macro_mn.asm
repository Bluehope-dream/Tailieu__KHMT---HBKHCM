
# -------------------------
# Subroutine: itoa_decimal
# Input: $a0 = integer value
#        $a1 = dest buffer address
# Output: buffer null-terminated string of decimal
# Clobbers: t-registers
# -------------------------
itoa_decimal:
    addi $sp,$sp,-32
    sw $ra,28($sp)
    sw $s0,24($sp)

    move $s0,$a1    # dest pointer
    move $t0,$a0    # value
    beq $t0,$zero,itoa_zero
    # build reversed digits at temp area (buf + 64)
    la $t1,buffer+64
    li $t2,0
itoa_loop:
    li $t3,10
    div	$t0,$t3
    mfhi $t4
    mflo $t0
    addi $t4,$t4,48
    sb $t4,0($t1)
    addi $t1,$t1,1
    addi $t2,$t2,1
    bne $t0,$zero,itoa_loop
    # reverse to dest
rev_itoa:
    addi $t1,$t1,-1
    lb $t4,0($t1)
    sb $t4,0($s0)
    addi $s0,$s0,1
    addi $t2,$t2,-1
    bgtz $t2,rev_itoa
    sb $zero,0($s0)
    j itoa_done

itoa_zero:
    li $t4,48
    sb $t4,0($s0)
    addi $s0,$s0,1
    sb $zero,0($s0)

itoa_done:
    lw $ra,28($sp)
    lw $s0,24($sp)
    addi $sp,$sp,32
    jr $ra

# -------------------------
# Subroutine: itoa_decimal_reg
# Input: $a0 = integer value, $a1 = dest address
# simply moves and calls itoa_decimal
# -------------------------
itoa_decimal_reg:
    move $t0,$a0
    move $a0,$t0
    move $a1,$a1
    jal itoa_decimal
    jr $ra

# -----------------------------------
# Float constants stored as labels (to load with l.s)
# -----------------------------------
	.data
.LC50000: .float 50000.0
.LC4:     .float 4.0
.LC05:    .float 0.5

# string "/50000\n" stored for easy append
str_slash_msg: .asciiz "/50000\n"
