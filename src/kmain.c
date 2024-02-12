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
  multiboot_module_t *modules = (multiboot_module_t *) mbinfo->mods_addr;

  for (unsigned int i = 0; mbinfo->flags & MULTIBOOT_INFO_MODS && i < mbinfo->mods_count; i++) {
    fb_info("launching module\n");
    unsigned int module_addr = modules[i].mod_start;

    call_module_t start_module = (call_module_t) module_addr;

    start_module();
    fb_info("end of module\n");
  }


  while (1) {
  }

  return 0;
}
