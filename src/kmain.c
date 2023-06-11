#include "io.h"
#include "fb.h"
#include "idt.h"
#include "pic.h"
#include "gdt.h"

int kmain(void) {

	gdt_init();
	/*
	pic_remap(PIC1, PIC2);

	struct idt_entry idt_entries[1];	
	init_entry(&idt_entries[0],  (unsigned int *) interrupt_handler_0, 1);
	load_idt( (unsigned int *) &idt_entries[0]);

	*/

	fb_info("Hello World !");

	while(1) {}

	return 0;
}
