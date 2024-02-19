#include "fb.h"
#include "idt.h"
#include "pic.h"
#include "gdt.h"
#include "multiboot_header.h"
#include "scheduler.h"

typedef void (*call_module_t)(void);

int kmain(unsigned int ebx) {

  gdt_init();
  pic_remap(PIC1_START_INTERRUPT, PIC2_START_INTERRUPT);
  idt_init();

  fb_info("Hello World !\n\n");

  multiboot_info_t *mbinfo = (multiboot_info_t *) ebx;
  multiboot_module_t *modules = (multiboot_module_t *) mbinfo->mods_addr;

  for (unsigned int i = 0; mbinfo->flags & MULTIBOOT_INFO_MODS && i < mbinfo->mods_count; i++) {
    //fb_info("launching module\n");
    unsigned int module_addr = modules[i].mod_start;

    struct stack_state st = {
      .eip = module_addr,
      .cs = 0x08,
    };

    struct process_state pstate = {
      .stack = st
    };

    sched_update_process(i, &pstate);
    // call_module_t start_module = (call_module_t) module_addr;
    // start_module();
    //fb_info("end of module\n");
  }

  call_module_t start_module = (call_module_t) modules[0].mod_start;
  start_module();

  while (1) {
  }

  return 0;
}
