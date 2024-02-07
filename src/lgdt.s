global load_gdt
global gdt_init_reg

; Loads the provided Global Descriptor Table (GDT)
; @param [esp + 4] 	The address of the GDT to load
; @return void
load_gdt:
	mov eax, [esp + 4]
	lgdt [eax]
	ret

; Loads the segments registers with the offsets for segments within GDT
; @return void
gdt_init_reg:
	mov ax, 0x10 ; ax is the accumulator register for arithmetic et logical operations
	mov ds, ax ; 0x10 - an offset into GDT for the third (kernel data segment) record.
	mov ss, ax ; ss is the stack segment register, store return addresses, local variables...
	mov es, ax ; es is the extra segment register, point on multi-segment program data
	mov fs, ax ; general purpose segment register
	mov gs, ax ; general purpose segment register

	jmp 0x08:flush_cs	; "far jump": jump to flush_cs and set cs to 0x08 (jump does nothing here but cs is set)
flush_cs:
	ret
