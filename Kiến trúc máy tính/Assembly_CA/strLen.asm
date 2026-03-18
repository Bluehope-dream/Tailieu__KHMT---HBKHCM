#####################
# ten chuong trinh : in ra doi dai chuoi
#######################
.include "macro.mac"
	.data
int_len: .word 13

#Cac cau nhap nhap 
str_a: .asciiz "DAI HOC BACK KHOA HCMUT"
xuat_len: asciiz "Do dai cua chuoi la: "
	################################
	#	Code Segment 
	################################3
	.text
main:
#Nhap chuoi 
	printString(str_a)
# xu ly:
	la $a0, str_a
	
	jal strlen
	sw $v0, int_len
# Xuat:
	printString(xuat_len)
	lw $t0, int_len
	printInteger($t0)
Ketthuc: 
	addi $v0,$zero,10
	syscall
#########################################
#	strlen: L?y chieu dau cua chuoi
#	#input: g?i chu?i
#	#output: tr? v? ?? dài chu?i = $v0
############################################
strlen:	
#while (s[i] !='\0')
#s[0] : address(a[i]) , s[0]=s[i], s1=i=0
	addi $s1,$zero,0
	
while:	lb $s0,0($a0)
	beq $s0,$zero,breakWhile
	addi $s1,$s1,1
	addi $a0,$a0,1
	j While
breakWhile:	add $v0,$s1,$zero
	jr $ra