# khai bao bien 

.data
sao: .asciiz "*" 
int_array: .space 40  #mang
filename: .asciiz "C:\\Users\\NGUYEN HUU TAY\\Downloads\\Assembly_CA\\string.txt"  #nho doi ten duong dan
error: .asciiz "Open with errors."
file_descriptor: .word 0

# -----------------------------------
# Code segment

.text
# Chuong trinh chinh
main:
    jal xu_ly_file #doc file va luu vao int_array
    # in day so trong file ra man hinh
    li $t0, 0 #tao bien dem cho vong lap, t0= 0

    lap_in_day_so_da_cho:
        lb $t1, int_array($t0)
        subi $t1, $t1, 48 #ma ascii -48 ra so thap phan, vi du 49-48=1
        bltz $t1, het_mang_in_day_so # t1 < 0 la ra ki tu la, khong in ki tu la ra man
        move $a0, $t1 #luu t1 vao a0
        addi $v0, $zero, 1 # in ra man hinh, syscall code = 1
        syscall
        het_mang_in_day_so:

            addi $t0, $t0, 1 #t0++
            blt $t0, 40, lap_in_day_so_da_cho # lap lai khi t<=40, do ?? yêu c?u m?ng 40 s?



    #ch? này b?t ??u thu?t toán in sao

    li $t5, 9 # ?ây là bi?n ??m s? hàng m?c ??nh t? 9 t?i 1
    in_xuong_dong:  # b?t ??u vòng l?p ngoài, cái này dùng ?? in xu?ng dòng
        addi $a0, $zero, '\n'
        addi $v0, $zero, 11
        syscall

        li $t0, 0
        lap_in_hang: # ?o?n này xét theo hàng, b?t ??u vòng l?p bên trong
            lb $t1, int_array($t0)
            subi $t1, $t1, 48
            bltz $t1, tiep_tuc_sau_in_sao #n?u mà t1<0 thì l?p ti?p v?i giá tr? k?
            bge $t1, $t5, in_sao # t1 == t5 ? in_sao
            addi $v0, $zero, 11
            addi $a0, $zero, ' '
            syscall  
            tiep_tuc_sau_in_sao:
                addi $t0, $t0, 1 # t0++
                blt $t0, 40, lap_in_hang  #thoát vòng l?p bên trong khi h?t chu?i 40 s?

        subi $t5, $t5, 1  #h? bi?n ??m dòng xu?ng
        bgtz $t5, in_xuong_dong  #quay l?i in xu?ng dòng

    j Kthuc #k?t thúc vòng l?p ngoài

#Hàm h? tr?

xu_ly_file: #Hàm x? lý file
    la $a0, filename
    addi $a1, $zero, 0
    addi $v0, $zero, 13
    syscall
    bltz $v0, baoloi
    sw $v0, file_descriptor

    lw $a0, file_descriptor
    la $a1, int_array
    addi $a2, $zero, 40
    addi $v0, $zero, 14
    syscall

    jr $ra

in_sao: # Hàm ?? in sao
    addi $v0, $zero, 4
    la $a0, sao
    syscall
    j tiep_tuc_sau_in_sao

baoloi: # Hàm thông báo l?i khi m? file không ???c
    la $a0, error
    addi $v0, $zero, 4
    syscall

    addiu $v0, $zero, 10
    syscall

Kthuc: # hàm k?t thúc
	addiu $v0,$zero,10
	syscall
