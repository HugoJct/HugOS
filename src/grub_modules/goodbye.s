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

mov edx, s5
mov eax, 0
int 0x28

;yield
;=======

mov edx, 1
mov eax, 1
int 0x28

;=======


ret

s0 equ 'B'
s1 equ 'y'
s2 equ 'e'
s5 equ 0x0A
