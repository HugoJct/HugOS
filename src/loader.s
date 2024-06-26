global loader                   ; the entry symbol for ELF
extern kmain

MAGIC_NUMBER 		equ 0x1BADB002     ; define the magic number constant
ALIGN_MODULES   equ 0x1
CHECKSUM     		equ -(MAGIC_NUMBER + ALIGN_MODULES) ; calculate the checksum

KERNEL_STACK_SIZE 	equ 16384

;===============================;
section .bss
align 4

kernel_stack:
	resb KERNEL_STACK_SIZE
;===============================;

;===============================;
section .text                  ; start of the text (code) section
align 4                         ; the code must be 4 byte aligned
    dd MAGIC_NUMBER             ; write the magic number to the machine code,
    dd ALIGN_MODULES
   	dd CHECKSUM                 ; and the checksum

loader:                         ; the loader label (defined as entry point in linker script)
   	mov eax, 0xCAFEBABE         ; place the number 0xCAFEBABE in the register 

	mov esp, kernel_stack + KERNEL_STACK_SIZE 	;initialize the stack pointer

  push ebx
	call kmain		;call main function 
;===============================;
