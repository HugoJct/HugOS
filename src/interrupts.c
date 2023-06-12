#include "idt.h"
#include "fb.h"
#include "pic.h"
#include "io.h"

#define IDT_MAX_DESCRIPTORS 256

extern void* isr_stub_table[];

static struct idt_entry _idt_entries[IDT_MAX_DESCRIPTORS] __attribute__((aligned(0x10)));

static struct idtr_t _table;

void idt_interrupt_handler(struct cpu_state cpu, unsigned int interrupt, struct stack_state stack) {

	(void) cpu;
	(void) stack;

	fb_info("Interruption fired");
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

	fb_info("[IDT] - Initialization...");

	_table.size = sizeof(struct idt_entry) * IDT_MAX_DESCRIPTORS - 1;
	_table.address = (unsigned int) _idt_entries;

	for(uint8_t i = 0; i < 32; i++) {

		idt_init_entry(&_idt_entries[i], isr_stub_table[i], 0x8E);
	}

	load_idt(&_table);

	fb_success("\tSuccess !");
}
