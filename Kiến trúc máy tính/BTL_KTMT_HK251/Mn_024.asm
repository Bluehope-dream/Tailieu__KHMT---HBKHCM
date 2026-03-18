#-----------------------------------
# Chuong trinh: Tao bieu do pho sao
# Cac ham: kiem_tra, ve_pho_sao
#-----------------------------------
.include "macro.mac"
#-----------------------------------
# Data segment
#-----------------------------------
.data
# Cac dinh nghia bien
file_input:     .asciiz "STRING.TXT"	
#LUU Y: - file STRING.TXT nam cung thu muc voi Mars4_5.jar
#       - Dan duong dan tuyet doi cua file vao trong dinh nghia
file_output:    .asciiz "PHO_SAO.TXT"
buffer_doc:     .space 41           # buffer cho chuoi dau vao (40 + null)
buffer_ghi:     .space 2000         # buffer cho output
# Cau thong bao loi
find_error:      .asciiz "File STRING.TXT khong hop le!\n"
#-----------------------------------
# Code segment
#-----------------------------------
.text
#-----------------------------------
# Chuong trinh chinh
#-----------------------------------
main:
    	# Mo file dau vao
    open_file(file_input, 0)        # che do 0: doc
    move $s0, $v0                   # luu file descriptor vao $s0
    bltz $s0, error                 # neu < 0 thi loi
    	# Doc noi dung file
    read_file($s0, buffer_doc, 41)  # Doc 41 byte de kiem tra
    move $s1, $v0                   # luu so byte doc duoc vao $s1
    	# Dong file dau vao
    close_file($s0)
    	# Kiem tra tinh hop le cua chuoi (chi chua 0-9, do dai <= 40)
    la $a0, buffer_doc
    move $a1, $s1
    jal kiem_tra
    move $s1, $v0                   # so ky tu hop le
    beqz $s1, error                 # neu = 0 thi khong hop le
    bgt $s1, 40, error              # neu > 40 thi khong hop le
    	# Goi ham tao bieu do pho sao
    la $a0, buffer_doc              # chuoi goc de in dong dau
    move $a1, $s1                   # so luong ky tu
    la $a2, buffer_ghi              # dia chi buffer output
    jal ve_pho_sao
    move $s2, $v0                   # luu do dai output vao $s2
    	# Mo file dau ra
    open_file(file_output, 9)       # che do 9: ghi + tao moi
    move $s3, $v0                   # luu file descriptor
    bltz $s3, error
    	# Ghi vao file
    write_file($s3, buffer_ghi, $s2)
    
    	# Dong file dau ra
    close_file($s3)
    
    	# In ra console de xem ket qua
    print_str(buffer_ghi)
    
    	# Ket thuc chuong trinh
    exit_program

# Xu ly loi
error:
    print_str(find_error)
    exit_program

#-----------------------------------
# Ham kiem_tra: Kiem tra chuoi chi chua 0-9
# I: $a0=addr(chuoi), $a1=so byte
# O: $v0=so ky tu chu so hop le (0 neu khong hop le)
# Reserved: none
#-----------------------------------
kiem_tra:
    	# t0=con tro, t1=so byte, t2=ky tu, t3=dem
    move $t0, $a0                   # con tro chuoi
    move $t1, $a1                   # so byte
    li $t3, 0                       # dem so chu so
    
# Vong lap kiem tra
loop_kt:
    beqz $t1, kt_done               # da kiem tra het
    lb $t2, 0($t0)                  # lay ky tu
    beqz $t2, kt_done               # gap null
    
    	# Kiem tra co phai chu so khong
    blt $t2, 48, kt_fail            # < '0' -> KHONG hop le
    bgt $t2, 57, kt_fail            # > '9' -> KHONG hop le
    
    	# Ky tu hop le
    addi $t3, $t3, 1                # tang dem
    addi $t0, $t0, 1                # toi ky tu tiep
    addi $t1, $t1, -1               # giam counter
    j loop_kt
    
kt_done:
    move $v0, $t3                   # tra ve so chu so hop le
    jr $ra
    
kt_fail:
    li $v0, 0                       # tra ve 0 (khong hop le)
    jr $ra

#-----------------------------------
# Ham ve_pho_sao: Tao bieu do pho sao theo chieu doc
# I: $a0=addr(chuoi goc), $a1=so ky tu, $a2=addr(buffer output)
# O: $v0=do dai chuoi output
# Reserved: $ra
#-----------------------------------
ve_pho_sao:
    	# Luu cac thanh ghi vao stack
    subi $sp, $sp, 16
    sw $ra, 12($sp)
    sw $s0, 8($sp)
    sw $s1, 4($sp)
    sw $s2, 0($sp)
    
    	# s0=addr(buffer), s1=so ky tu, s2=max
    	# t9=con tro ghi
    move $s0, $a2                   # luu dia chi buffer output
    move $s1, $a1                   # so luong ky tu
    move $t9, $a2                   # con tro ghi vao buffer
    
    	# Dong dau tien: in chuoi so goc
    	# t8=chuoi goc, t7=so ky tu, t6=ky tu
    move $t8, $a0                   # chuoi goc
    move $t7, $s1                   # so ky tu
    
# Vong lap in dong dau
in_dong1:
    beqz $t7, dong1_done            # het chuoi
    lb $t6, 0($t8)                  # lay ky tu
    sb $t6, 0($t9)                  # ghi vao buffer
    addi $t9, $t9, 1                # tang con tro
    addi $t8, $t8, 1                # toi ky tu tiep
    addi $t7, $t7, -1               # giam counter
    j in_dong1
    
dong1_done:
    li $t6, 10                      # newline
    sb $t6, 0($t9)                  # ghi newline
    addi $t9, $t9, 1
    
    	# Tim gia tri max de biet can ve bao nhieu hang
    	# t0=con tro, t1=max, t2=so ky tu, t3=ky tu, t4=gia tri
    move $t0, $a0                   # chuoi goc
    li $t1, 0                       # max = 0
    move $t2, $s1                   # so ky tu
    
# Vong lap tim max
tim_max:
    beqz $t2, max_done              # het chuoi
    lb $t3, 0($t0)                  # lay ky tu
    sub $t4, $t3, 48                # chuyen thanh so (char - '0')
    bgt $t4, $t1, update_max        # neu > max
    j next_max
    
update_max:
    move $t1, $t4                   # cap nhat max
    
next_max:
    addi $t0, $t0, 1                # toi ky tu tiep
    addi $t2, $t2, -1               # giam counter
    j tim_max
    
max_done:
    move $s2, $t1                   # $s2 = max_value
    
    	# Ve bieu do tu tren xuong duoi (tu max xuong 1)
    	# s2=level hien tai
ve_chart:
    beqz $s2, chart_done            # da ve het
    
    	# Ve mot hang: duyet qua tung vi tri
    	# t0=con tro, t1=so ky tu, t2=ky tu, t3=gia tri
    move $t0, $a0                   # chuoi goc
    move $t1, $s1                   # so ky tu
    
# Vong lap ve hang
ve_row:
    beqz $t1, row_done              # da ve het cac cot
    
    lb $t2, 0($t0)                  # lay ky tu
    sub $t3, $t2, 48                # chuyen thanh gia tri (char - '0')
    
    	# So sanh gia tri voi level hien tai
    bge $t3, $s2, in_sao            # neu value >= level thi in sao
    
    	# In space
    li $t4, 32                      # space
    sb $t4, 0($t9)                  # ghi space
    addi $t9, $t9, 1                # tang con tro
    j next_col
    
in_sao:
    li $t4, 42                      # '*'
    sb $t4, 0($t9)                  # ghi sao
    addi $t9, $t9, 1                # tang con tro
    
next_col:
    addi $t0, $t0, 1                # toi ky tu tiep theo
    addi $t1, $t1, -1               # giam counter
    j ve_row
    
row_done:
    li $t4, 10                      # newline
    sb $t4, 0($t9)                  # ghi newline
    addi $t9, $t9, 1                # tang con tro
    
    subi $s2, $s2, 1                # giam level
    j ve_chart
    
chart_done:
    sb $zero, 0($t9)                # null terminator
    
    	# Tinh do dai output
    sub $v0, $t9, $s0               # do dai = con tro hien tai - dia chi dau
    
    	# Lay cac thanh ghi tu stack
    lw $s2, 0($sp)
    lw $s1, 4($sp)
    lw $s0, 8($sp)
    lw $ra, 12($sp)
    addi $sp, $sp, 16
    jr $ra
#-----------------------------------
