# Chuong trinh : nhap tinh toan cac hang tu cua  toan hang 
	.data
###################################
#	data segment 
###################################
int_a : .word 0
int_b: .word   0
int_c: .word   0
int_f: .word 13
# CAU NHAC NHAP CAC TOAN HANG
nhap_a: .asciiz "Moi ban nhap f(a): "
nhap_b: .asciiz "Moi ban nhap f(b): "
nhap_c: .asciiz "Moi ban nhap f(c): "
xuat_f : .asciiz  "Toi se xuat f(a,b,c): "

	.text
##################################
#	Code Segment 
##################################

main:
#Syscall g?i l?nh nh?p 

#Nhap a
	geti_p nhap_a,int_a
	
#Nhap b
	geti_p nhap_b,int_b
#Nhap c
	geti_p nhap_c,int_c

#Xu ly bai toan 
	lw $t0, int_a
	lw $t1, int_b
	sub $t0, $t0,$t1
	lw $t1, int_c
	add $t0, $t0,$t1
	sw $t0, int_f
#Xuat ket qua cua bai toan 
	puti_p xuat_f,int_f

Ketthuc:	addi $v0,$zero,10
	syscall


	