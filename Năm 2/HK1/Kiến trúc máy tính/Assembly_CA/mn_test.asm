# Chuong trinh: tinh so pi in ra dinh dang nhu mau 
#----------------------------------------------
#	Input:     Sinh 50000 so ngau nhien (x,y) tu (0,1) 
#	Output:    In ra man hinh va file theo dinh dang sau:
#			- So diem nam trong hinh tron: ddddd/50000
#			- So PI tinh duoc: f.fffff
#
#-----------------------------------------------
	.data
# --- Dinh nghia bien ---
seed:       .word   0
float1:     .float  0.25    # R^2 = 0.5^2
float2:     .float  0.5     # Tam (0.5, 0.5)
const4:     .float  4.0     # He so nhan
f_100k:     .float  100000.0 # He so lay 5 so sau dau phay
PI_val:     .float  0.0

# --- Duong dan file (Sua lai duong dan cua ban neu can) ---
PI_file:    .asciiz "C:/Users/NGUYEN HUU TAY/Downloads/Assembly_CA/PI.TXT"

# --- Cac chuoi ky tu ---
str1:       .asciiz "So diem nam trong hinh tron: "
slash:      .asciiz "/50000"
newline:    .asciiz "\r\n"   # Xuong dong Windows
str2:       .asciiz "So PI tinh duoc: "
dot:        .asciiz "."
padding:    .asciiz "0"      # Dung de chen so 0 neu can

# Buffer chuyen doi so sang chuoi
buffer:     .space  20

	.text
	.globl main

main:
    # 1. Khoi tao Random Seed (De moi lan chay ra ket qua khac nhau)
    li      $v0, 30          # Lay thoi gian he thong
    syscall
    sw      $v0, seed
    
    # Set seed (Syscall 40)
    move    $a0, $v0
    li      $a1, 0           
    li      $v0, 40
    syscall

    # 2. Khoi tao cac bien dem
    li      $t0, 0           # $t0: Dem so diem trong tron
    li      $t1, 50000       # $t1: Tong so diem (Loop counter)
    l.s     $f2, float1      # $f2 = 0.25
    l.s     $f4, float2      # $f4 = 0.5

start_loop:
    # --- FIX QUAN TRONG: SINH SO NGAU NHIEN ---
    
    # Sinh Y (Luu vao $f1)
    li      $a0, 0
    li      $v0, 43          # Random float (0.0 -> 1.0)
    syscall
    mov.s   $f1, $f0         # Chuyen gia tri random tu $f0 sang $f1

    # Sinh X (Luu vao $f0)
    li      $a0, 0
    li      $v0, 43          # Random float thu 2
    syscall
    # Bay gio $f0 la X, $f1 la Y (Khac nhau)

    # --- Tinh toan hinh hoc ---
    # Tinh (x - 0.5)^2
    sub.s   $f5, $f0, $f4    
    mul.s   $f5, $f5, $f5    # $f5 = (x-0.5)^2
    
    # Tinh (y - 0.5)^2
    sub.s   $f6, $f1, $f4    
    mul.s   $f6, $f6, $f6    # $f6 = (y-0.5)^2

    add.s   $f7, $f5, $f6    # $f7 = Tong binh phuong

    # Kiem tra dieu kien <= 0.25
    c.le.s  $f7, $f2
    bc1f    not_in_circle

in_circle:
    addi    $t0, $t0, 1      # Tang bien dem

not_in_circle:
    addi    $t1, $t1, -1     # Giam loop counter
    bnez    $t1, start_loop  # Lap lai neu chua du 50000

    # --- KET THUC VONG LAP ---

    # Tinh PI = (count / 50000) * 4
    mtc1    $t0, $f0         # Chuyen int count sang float
    cvt.s.w $f0, $f0
    
    li      $t2, 50000
    mtc1    $t2, $f1
    cvt.s.w $f1, $f1
    
    div.s   $f12, $f0, $f1   # Ty le = count/50000
    l.s     $f8, const4
    mul.s   $f12, $f12, $f8  # PI = Ty le * 4
    s.s     $f12, PI_val     # Luu ket qua PI

    # ==========================================
    # XUAT RA MAN HINH (CONSOLE)
    # ==========================================
    
    # In dong 1
    li      $v0, 4
    la      $a0, str1
    syscall

    li      $v0, 1
    move    $a0, $t0         # So diem
    syscall
    
    li      $v0, 4
    la      $a0, slash
    syscall
    li      $v0, 4
    la      $a0, newline
    syscall
    # In dong 2
    li      $v0, 4
    la      $a0, str2
    syscall

    li      $v0, 2           # In float
    l.s     $f12, PI_val
    syscall
    
    li      $v0, 4
    la      $a0, newline
    syscall

    # ==========================================
    #  GHI VAO FILE PI.TXT
    # ==========================================
    
    # Mo file
    li      $v0, 13
    la      $a0, PI_file
    li      $a1, 1           
    li      $a2, 0
    syscall
    move    $s0, $v0         # Luu file 
    # Kiem tra loi mo file
    bltz    $s0, end_program
    # Ghi "So diem nam trong hinh tron: "
    move    $a0, $s0
    la      $a1, str1
    li      $a2, 29
    li      $v0, 15
    syscall
    # 3. Ghi so diem 
    move    $a0, $t0
    jal     int2str          # Chuyen so thanh chuoi
    
    move    $a0, $s0
    la      $a1, buffer
    move    $a2, $v1         # Do dai chuoi
    li      $v0, 15
    syscall

    # 4. Ghi "/50000" va xuong dong
    move    $a0, $s0
    la      $a1, slash
    li      $a2, 6           # Do dai "/50000"
    li      $v0, 15
    syscall
    
    move    $a0, $s0
    la      $a1, newline
    li      $a2, 2
    li      $v0, 15
    syscall

    # 5. Ghi "So PI tinh duoc: "
    move    $a0, $s0
    la      $a1, str2
    li      $a2, 17
    li      $v0, 15
    syscall

    # --- GHI SO THUC (FLOAT) vao FILE ---
    # Xu ly phan nguyen
    l.s     $f12, PI_val     # Load lai PI
    cvt.w.s $f10, $f12       # Chuyen PI ve Int (vd: 3)
    mfc1    $t5, $f10        # $t5 = 3
    
    # Ghi phan nguyen
    move    $a0, $t5
    jal     int2str
    move    $a0, $s0
    la      $a1, buffer
    move    $a2, $v1
    li      $v0, 15
    syscall

    # Ghi dau cham "."
    move    $a0, $s0
    la      $a1, dot
    li      $a2, 1
    li      $v0, 15
    syscall

    # Xu ly phan thap phan
    cvt.s.w $f11, $f10       # $f11 = 3.0
    sub.s   $f13, $f12, $f11 # $f13 = 0.14159...
    
    # lay 5 chu so thap phan cho PI
    l.s     $f14, f_100k
    mul.s   $f13, $f13, $f14 
    cvt.w.s $f13, $f13       
    mfc1    $t6, $f13
    abs     $t6, $t6        # Lay tri tuyet doi de tranh loi

    # Kiem tra neu phan thap phan < 10000 thi thieu so 0
    li      $t7, 10000
    bge     $t6, $t7, write_decimal # Neu >= 10000
    
    # Neu nho hon, can them so 0 CHO DUNG DINH DANG
    move    $a0, $s0
    la      $a1, padding     # Ghi them so '0'
    li      $a2, 1
    li      $v0, 15
    syscall
    
write_decimal:
    move    $a0, $t6
    jal     int2str
    move    $a0, $s0
    la      $a1, buffer
    move    $a2, $v1
    li      $v0, 15
    syscall

    # Dong file
    move    $a0, $s0
    li      $v0, 16
    syscall

end_program:
    li      $v0, 10
    syscall

# -----------------------------------------------------------
# Ham con: int2str (Chuyen so nguyen $a0 sang chuoi buffer)
# Output: $v1 la do dai chuoi
# -----------------------------------------------------------
int2str:
    la      $t8, buffer      
    add     $t8, $t8, 10     # Tro vao giua buffer
    sb      $zero, 0($t8)    # Null terminator
    li      $v1, 0           
    
    move    $t9, $a0         # Lay so can chuyen
    
    # Xu ly so 0
    bnez    $t9, convert_loop
    addi    $t8, $t8, -1
    li      $t3, 48          # '0'
    sb      $t3, 0($t8)
    li      $v1, 1
    j       int2str_done

convert_loop:
    blez    $t9, int2str_done 
    div     $t9, $t9, 10     # Chia 10
    mfhi    $t3              # Lay so du
    addi    $t3, $t3, 48     # ASCII
    addi    $t8, $t8, -1
    sb      $t3, 0($t8)
    addi    $v1, $v1, 1
    j       convert_loop

int2str_done:
    # Copy ve dau buffer
    la      $t4, buffer
copy_loop:
    lb      $t3, 0($t8)
    sb      $t3, 0($t4)
    beqz    $t3, finish_copy
    addi    $t8, $t8, 1
    addi    $t4, $t4, 1
    j       copy_loop
finish_copy:
    jr      $ra
