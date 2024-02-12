#include "idt.h"
#include "fb.h"
#include "pic.h"
#include "io.h"
#include "keyboard.h"

#define IDT_MAX_DESCRIPTORS 256

extern void* isr_stub_table[];

static struct idt_entry _idt_entries[IDT_MAX_DESCRIPTORS] __attribute__((aligned(0x10)));

static struct idtr_t _table;

void idt_interrupt_handler(struct cpu_state cpu, unsigned int interrupt, struct stack_state stack) {

	(void) stack;

	switch(interrupt) {
		case 0:
			fb_error("Division Error !");
			break;
    case 6:
			fb_error("Invalid opcode !");
      break;
		case 8:
			fb_error("Double Fault !");
			break;
		case 14:
			fb_error("Page Fault !");
			break;
		case 13:
			fb_error("General Protection Fault !");
			break;
		case 33:
			keyboard_handle_interruption();
			break;
    case 40:  //syscalls
      switch(cpu.eax) {
        case 0:
          char str[] = {
            (char) cpu.edx,
            (char) 0,
          };
          fb_info(str);
          break;
        default:
          fb_info("unknown syscall\n");
          break;
      }
      break;
		default:
			fb_info("Interruption fired !");
	}

	pic_acknowledge(interrupt);
}

static void idt_init_entry(struct idt_entry *entry, void *function, uint8_t flags) {

	entry->isr_low = (uint32_t) function & 0xFFFF;	
	entry->kernel_cs = 0x08;
	entry->reserved = 0;
	entry->attributes = flags;
	entry->isr_high = (uint32_t) function >> 16;
}

void idt_init() {

	fb_info("[IDT] - Initialization...\n");

	_table.size = sizeof(struct idt_entry) * IDT_MAX_DESCRIPTORS - 1;
	_table.address = (unsigned int) _idt_entries;

	for(uint8_t i = 0; i < 41; i++) {

		idt_init_entry(&_idt_entries[i], isr_stub_table[i], 0x8E);
	}

	load_idt(&_table);

	fb_success("\tSuccess !\n");
}
