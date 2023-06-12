#include "fb.h"
#include "idt.h"
#include "pic.h"
#include "gdt.h"

int kmain(void) {

	gdt_init();
	pic_remap(0x20, 0x28);
	idt_init();

	fb_info("Hello World !");

	while(1) {}

	return 0;
}
