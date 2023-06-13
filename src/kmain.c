#include "fb.h"
#include "idt.h"
#include "pic.h"
#include "gdt.h"

int kmain(void) {

	gdt_init();
	pic_remap(PIC1_START_INTERRUPT, PIC2_START_INTERRUPT);
	idt_init();

	fb_info("Hello World !\n");

	while(1) {
		int i = 0;
		i += 1;
	}

	return 0;
}
