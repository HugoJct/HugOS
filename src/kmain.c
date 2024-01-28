#include "fb.h"
#include "idt.h"
#include "pic.h"
#include "gdt.h"
#include "multiboot_header.h"

typedef void (*call_module_t)(void);

int kmain(unsigned int ebx) {

	gdt_init();
	pic_remap(PIC1_START_INTERRUPT, PIC2_START_INTERRUPT);
	idt_init();

	fb_info("Hello World !\n");

  multiboot_info_t *mbinfo = (multiboot_info_t *) ebx;
  unsigned int infinite_loop_module = mbinfo->mods_addr;

  call_module_t start_infinite = (call_module_t) infinite_loop_module;

  start_infinite();
  while(1) {
    fb_info("loop");
  }

	return 0;
}
