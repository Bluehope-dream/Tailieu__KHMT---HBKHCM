# chuong trinh : in ra chuoi nho hon 10 ki tu 
	.include "macro.mac"

#Khai bao data segment
	.data
# Dinh nghia cac bien 
buffer: .space 11
#Cac cau nhac nhap du lieu
nhap_s:  .asciiz "Nhap chuoi(<=10 ky tu):"
xuat_s : .asciiz " Chuoi da nhap: "
#--------------------------------
#   Code segment'
#--------------------------------------
	.text
#--------------------------------
#   Chuong trinh chinh
#--------------------------------------
main:
#Nhap syscall
	puts nhap_s
	la $a0,buffer
	addi $a1,$zero,11
	addi $v0,$zero,8
	syscall
# Xuong dong
	linefeed   #putch('\n')
#Xu ly 
#Xuat ket qua (syscall)
	puts_p xuat_s,buffer
	
#Ket thuc chuong trinh
Ketthuc:	addi  $v0,$zero,10
	syscall
