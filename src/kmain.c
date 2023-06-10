#include "io.h"
#include "fb.h"
#include "idt.h"
#include "pic.h"

int kmain(void) {

	pic_remap();

	struct idt_entry idt_entries[1];	
	init_entry(&idt_entries[0],  (unsigned int *) interrupt_handler_0, 0);
	load_idt( (unsigned int *) &idt_entries[0]);

	char *str = "Hello World !\n";

	fb_clear();
	fb_set_color(FB_GREEN, FB_BLACK);
	fb_write(str);

	while(1) {}

	return 0;
}
