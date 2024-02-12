BITS 32

mov edx, [string + 1]
mov eax, 0
int 0x28
ret

string:
  db "Hello", 0
