BITS 32

mov edx, s0
mov eax, 0
int 0x28

mov edx, s1
mov eax, 0
int 0x28

mov edx, s2
mov eax, 0
int 0x28

mov edx, s3
mov eax, 0
int 0x28

;yield
;=======

mov edx, 0
mov eax, 1
int 0x28

;=======

mov edx, s4
mov eax, 0
int 0x28

mov edx, s5
mov eax, 0
int 0x28

ret

s0 equ 'H'
s1 equ 'e'
s2 equ 'l'
s3 equ 'l'
s4 equ 'o'
s5 equ 0x0A
