global load_gdt
global gdt_init_reg

load_gdt:
	mov eax, [esp + 4]
	lgdt [eax]

	call gdt_init_reg	

	ret

gdt_init_reg:
	mov eax, 0x10
	mov ds, eax
	mov ss, eax
	mov es, eax
	mov fs, eax
	mov gs, eax
	
	jmp 0x08:flush_cs
flush_cs:
	ret
