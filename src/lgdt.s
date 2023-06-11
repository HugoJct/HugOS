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
	mov ax, 0x10
	mov ds, ax ; 0x10 - an offset into GDT for the third (kernel data segment) record.
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	jmp 0x08:flush_cs	; "far jump": jump to flush_cs and set cs to 0x08 (jump does nothing here but cs is set)
flush_cs:
	ret
