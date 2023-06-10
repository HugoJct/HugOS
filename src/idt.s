global load_idt
; load_idt - Loads the interrupt descriptor table (IDT).
; stack: [esp + 4] the address of the first entry in the IDT
; [esp] the return address

load_idt:
	mov eax, [esp + 4] ; load the address of the IDT into register eax
	lidt [eax] ; load the IDT
	ret ; return to the calling function

%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1

interrupt_handler_%1:
	push dword 0
	push dword %1
	jmp common_interrupt_handler

%endmacro

%macro error_code_interrupt_handler 1
global interrupt_handler_%1

interrupt_handler_%1:
	push dword %1
	jmp common_interrupt_handler

%endmacro

common_interrupt_handler:
	push eax
	push ecx
	push edx
	push ebx
	push esp
	push ebp
	push esi
	push edi

	extern interrupt_handler
	call interrupt_handler

	pop edi
	pop esi
	pop ebp
	pop esp
	pop ebx
	pop edx
	pop ecx
	pop eax

	add esp, 8
	iret


no_error_code_interrupt_handler 0
no_error_code_interrupt_handler 1
no_error_code_interrupt_handler 2
no_error_code_interrupt_handler 3
no_error_code_interrupt_handler 4
no_error_code_interrupt_handler 5
no_error_code_interrupt_handler 6
no_error_code_interrupt_handler 7
no_error_code_interrupt_handler 9
no_error_code_interrupt_handler 15
no_error_code_interrupt_handler 16

error_code_interrupt_handler 8
error_code_interrupt_handler 10
error_code_interrupt_handler 11
error_code_interrupt_handler 12
error_code_interrupt_handler 13
error_code_interrupt_handler 14
error_code_interrupt_handler 17
