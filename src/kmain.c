#include "io.h"
#include "fb.h"
#include "idt.h"
#include "pic.h"
#include "gdt.h"

int kmain(void) {

	fb_clear();
	fb_set_color(FB_GREEN, FB_BLACK);

	gdt_init();
	/*
	pic_remap(PIC1, PIC2);

	struct idt_entry idt_entries[1];	
	init_entry(&idt_entries[0],  (unsigned int *) interrupt_handler_0, 1);
	load_idt( (unsigned int *) &idt_entries[0]);

	*/
	char *str = "Hello World !\n";

	fb_write(str);

	while(1) {}

	return 0;
}
