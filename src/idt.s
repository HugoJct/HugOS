global load_idt
; load_idt - Loads the interrupt descriptor table (IDT).
; stack: [esp + 4] the address of the first entry in the IDT
; [esp] the return address

load_idt:
	mov eax, [esp + 4] ; load the address of the IDT into register eax
	lidt [eax] ; load the IDT
	sti
	ret

%macro no_error_code_interrupt_handler 1
interrupt_handler_%1:
	push dword 0
	push dword %1

	jmp common_interrupt_handler
%endmacro

%macro error_code_interrupt_handler 1
interrupt_handler_%1:
	push dword %1

	jmp common_interrupt_handler
%endmacro

common_interrupt_handler:
	push edi
	push esi
	push ebp
	push esp
	push ebx
	push edx
	push ecx
	push eax

	extern idt_interrupt_handler
	call idt_interrupt_handler

	pop eax
	pop ecx
	pop edx
	pop ebx
	pop esp
	pop ebp
	pop esi
	pop edi

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
error_code_interrupt_handler    8
no_error_code_interrupt_handler 9
error_code_interrupt_handler    10
error_code_interrupt_handler    11
error_code_interrupt_handler    12
error_code_interrupt_handler    13
error_code_interrupt_handler    14
no_error_code_interrupt_handler 15
no_error_code_interrupt_handler 16
error_code_interrupt_handler    17
no_error_code_interrupt_handler 18
no_error_code_interrupt_handler 19
no_error_code_interrupt_handler 20
no_error_code_interrupt_handler 21
no_error_code_interrupt_handler 22
no_error_code_interrupt_handler 23
no_error_code_interrupt_handler 24
no_error_code_interrupt_handler 25
no_error_code_interrupt_handler 26
no_error_code_interrupt_handler 27
no_error_code_interrupt_handler 28
no_error_code_interrupt_handler 29
error_code_interrupt_handler    30
no_error_code_interrupt_handler 31

global isr_stub_table
isr_stub_table:
%assign i 0 
%rep    32 
    dd interrupt_handler_%+i
%assign i i+1 
%endrep
