# Chuong trinh: tim so PI tren random khao sat cua 50000 diem
#-----------------------------------------
#	Input: Sinh 50000 diem  (0<x<1,0<y<1)
#	Output:    - Xac dinh so Pi 
#		 - Luu ket qua vao tap  tin PI.TXT
#		    + So diem nam  trong hinh tron 
#		    + So PI tinh dc : f.fffff
#-----------------------------------------
	.include "macro_mn.asm"
#-----------------------------------
# 		Data segment
#-----------------------------------
	.data
# Cac dinh nghia bien
seed:   .word   0
float1:	.float 	0.25
float2:	.float	0.5
diem:	.word	0
PI:	.float	0.0
# Cac cau nhac nhap du lieu
PI_file:.asciiz "PI.txt"
str1:	.asciiz "So diem nam trong hinh tron: "
newline:.asciiz "\n"
str2:	.asciiz "So PI tinh duoc: "
buffer: .space 128        # buffer de dung chuyen so -> chuoi
buf2:   .space 128        # buffer phu de format PI
#-------------------------------------
# 		Code segment
#-------------------------------------
	.text
	.globl main
main:

    	# Dat seed de tao so ngau nhien
    	li 	$v0,30
    	syscall
    	sw 	$v0,seed		# Luu time  seed =30

    	# Set seed cho syscall 43 (phai truyen seed qua $a0)
    	lw	$a0,seed
    	li	$v0,40
    	syscall

    	li 	$v0,13        	# syscall 13 - Mo file
        la 	$a0,PI_file   	# load dia chi file
        li 	$a1,1         	# Mo file de ghi (write/create)
        li 	$a2,0         	# Mode file
        syscall
        move 	$s0,$v0     	# Luu file mo ta vao $s0

    	# Khoi tao bien
    	li 	$t0,0         	# Bien t0 dem so diem nam trong hinh tron
    	li	$t1,50000    	# Tong so diem ngau nhien (50000)
    	l.s	$f2,float1	# Dat f2 la 0.25
    	l.s	$f4,float2	# Dat f4 la 0.5
    	la	$t5,buffer	# t5 luu ket qua can in ra (buffer)
    	
start_loop:		# Khoi tao vong lap random check dieu kien
    	beq	$t1,$zero,after_loop

    	# Tao x ngau nhien -> luu vao f12
    	li 	$v0,43
    	syscall
    	mov.s 	$f12,$f0		# random x

    	# Tao y ngau nhien -> luu vao f0
    	li 	$v0,43
    	syscall
    	mov.s 	$f0,$f0		# random y (da o f0)

    	# Tinh (x-0.5)^2
    	sub.s	$f6,$f12,$f4	# f6 = x - 0.5
    	mul.s 	$f6,$f6,$f6  	# f6 = (x-0.5)^2

    	# Tinh (y-0.5)^2
    	sub.s	$f7,$f0,$f4	# f7 = y - 0.5
    	mul.s 	$f7,$f7,$f7  	# f7 = (y-0.5)^2

    	# Kiem tra xem diem do nam trong hinh tron tam O(0.5;0.5) ban kinh 0.5 hay khong
    	add.s 	$f3,$f6,$f7  	# f3 = (x-0.5)^2 + (y-0.5)^2
    	c.le.s 	$f3,$f2    	# check dk : (x-0.5)^2 + (y-0.5)^2 <= 0.25?  	
    	bc1t 	count_Index 

    	# Khong nam trong hinh tron -> chi giam so diem con phai sinh
    	addi 	$t1,$t1,-1
    	j		start_loop

count_Index:
    	addi 	$t0,$t0,1  	# Tang so diem tim duoc them 1
    	addi 	$t1,$t1,-1    # Chi giam 1 lan (da tinh 1 diem)
    	j		start_loop

after_loop:
# Xuat ket qua 	
# In ra so diem nam trong hinh tron yeu cau
    	li 	$v0,4
    	la 	$a0,str1
    	syscall

    	li	$v0,1		
    	move	$a0,$t0
    	syscall

    	sw	$t0,diem	# Luu so diem trong hinh tron la gia tri t0

    	# Xuong hang
    	li 	$v0,4
    	la 	$a0,newline
    	syscall

# Tinh toan va in ra so PI
    	li 	$v0,4    
    	la 	$a0,str2
    	syscall

# PI = (t0/50000)*4
    	l.s    $f8, float2      # f8 = 0.5 (reuse)
    	li	$v0,2        # (we'll compute float then print)
    	# chuyen t0 -> float va tinh PI
    	mtc1 	$t0,$f0
    	cvt.s.w $f0,$f0
    	l.s	$f6, .LC50000    # load 50000.0
    	div.s	$f1,$f0,$f6    # f1 = t0 / 50000.0
    	l.s	$f2, .LC4        # load 4.0
    	mul.s	$f12,$f1,$f2   # f12 = PI
    	syscall
    	s.s	$f12,PI		# Luu Pi la gia tri f12
    	
    	# Xuong hang
    	li 	$v0,4
    	la 	$a0,newline
    	syscall

# --- CHU Y: ta phai khai bao h?ng float 50000.0 và 4.0 -> ??t ? cu?i data ---
# Ghi ket qua vao file PI.txt
# Ghi str1
    	move 	$a0,$s0  	# File mo ta
        li 	$v0,15         	# syscall 15 - Ghi file
        la  	$a1,str1      	# Dia chi bo dem chua noi dung
    	# tinh do dai str1
    	# (dùng reg t6,t7)
    	la	$t6,str1
    	li	$t7,0
len1:
    	lb	$t8,0($t6)
    	beq	$t8,$zero,len1_done
    	addi	$t7,$t7,1
    	addi	$t6,$t6,1
    	j	len1
len1_done:
    	move	$a2,$t7
        syscall

# Ghi so diem (chuyen int -> buffer va ghi "/50000\n")
    	# chuyen integer t0 -> ascii trong buffer
    	move	$a0,$t0       # value
    	la	$a1,buffer
    	jal	itoa_decimal   # sau khi tra ve, buffer chua chuoi null-terminated

    	# noi "/50000\n" vao sau chuoi
    	la	$t6,buffer
find_end_buf:
    	lb	$t7,0($t6)
    	beq	$t7, $zero, append_slash
    	addi	$t6,$t6,1
    	j	find_end_buf
append_slash:
    	la	$t8,str1       # reuse str1? nah, use str_slash stored in newline+... but simpler:
    	# chu y: ta da co newline, va muon ghi "/50000\n" -> tao nhanh trong buf2
    	la	$t9,str_slash_msg
copy_slash_loop:
    	lb	$t7,0($t9)
    	sb	$t7,0($t6)
    	beq	$t7,$zero,done_copy_slash
    	addi	$t9,$t9,1
    	addi	$t6,$t6,1
    	j	copy_slash_loop
done_copy_slash:
    	# ghi buffer ra file
    	move	$a0,$s0
    	li	$v0,15
    	la	$a1,buffer
    	# tinh len buffer
    	la	$t6,buffer
    	li	$t7,0
lenbuf:
    	lb	$t8,0($t6)
    	beq	$t8,$zero,lenbuf_done
    	addi	$t7,$t7,1
    	addi	$t6,$t6,1
    	j	lenbuf
lenbuf_done:
    	move	$a2,$t7
    	syscall

# Ghi str2
    	move 	$a0,$s0
        li 	$v0,15
        la  	$a1,str2
    	# len str2
    	la	$t6,str2
    	li	$t7,0
len2:
    	lb	$t8,0($t6)
    	beq	$t8,$zero,len2_done
    	addi	$t7,$t7,1
    	addi	$t6,$t6,1
    	j	len2
len2_done:
    	move	$a2,$t7
        syscall

# Ghi PI dang f.fffff (lam tron 5 chu so)
    	# lay PI tu $f12
    	# N = int(PI*100000 + 0.5)
    	li	$t2,100000
    	mtc1	$t2,$f10
    	mul.s	$f14,$f12,$f10   # f14 = PI * 100000
    	l.s	$f15, .LC05        # 0.5
    	add.s	$f14,$f14,$f15
    	cvt.w.s $f14,$f14
    	mfc1	$t3,$f14        # t3 = rounded int

    	# t3 -> integer part / fractional
    	li	$t4,100000
    	div	$t3,$t4
    	mflo	$t5	# integer part
    	mfhi	$t6	# fractional part (0..99999)

    	# tao chuoi: integerpart '.' fractional(5digits) '\n' '\0' -> buf2
    	la	$a1,buf2
    	move	$a0,$t5
    	jal	itoa_decimal_reg  # ket qua o buf2

    	# tim cuoi
    	la	$t7,buf2
find_end_buf2:
    	lb	$t8,0($t7)
    	beq	$t8,$zero,put_dot
    	addi	$t7,$t7,1
    	j	find_end_buf2
put_dot:
    	li	$t8,46    # '.'
    	sb	$t8,0($t7)
    	addi	$t7,$t7,1

    	# write 5 digits of fractional (pad leading zeros)
    	# t6 has 0..99999
    	li	$t9,10000
    	move	$k0,$t6
digit1:
    	div	$k0,$t9
    	mflo	$k1
    	mfhi	$k0
    	addi	$k1,$k1,48
    	sb	$k1,0($t7)
    	addi	$t7,$t7,1
    	li	$t9,1000
    	div	$k0,$t9
    	mflo	$k1
    	mfhi	$k0
    	addi	$k1,$k1,48
    	sb	$k1,0($t7)
    	addi	$t7,$t7,1
    	li	$t9,100
    	div	$k0,$t9
    	mflo	$k1
    	mfhi	$k0
    	addi	$k1,$k1,48
    	sb	$k1,0($t7)
    	addi	$t7,$t7,1
    	li	$t9,10
    	div	$k0,$t9
    	mflo	$k1
    	mfhi	$k0
    	addi	$k1,$k1,48
    	sb	$k1,0($t7)
    	addi	$t7,$t7,1
    	# last digit
    	addi	$k0,$k0,48
    	sb	$k0,0($t7)
    	addi	$t7,$t7,1

    	# newline + terminate
    	li	$k1,10
    	sb	$k1,0($t7)
    	addi	$t7,$t7,1
    	sb	$zero,0($t7)

    	# ghi buf2 vao file
    	move	$a0,$s0
    	li	$v0,15
    	la	$a1,buf2
    	# tinh len buf2
    	la	$t7,buf2
    	li	$t8,0
lenbuf2:
    	lb	$k1,0($t7)
    	beq	$k1,$zero,lenbuf2_done
    	addi	$t8,$t8,1
    	addi	$t7,$t7,1
    	j	lenbuf2
lenbuf2_done:
    	move	$a2,$t8
    	syscall

# Dong file
        move 	$a0,$s0		# File mo ta
        li 	$v0,16		# syscall 16 - Dong file
        syscall

# Ket thuc chuong trinh
Ketthuc:	addi $v0,$zero,10
    	syscall
