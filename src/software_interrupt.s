global inter

; int - invokes a software interrupts 
; [esp + 4] interrupt number
inter:
  mov eax, [esp + 4]
  int 0x28 ; 41 base 10
  ret
