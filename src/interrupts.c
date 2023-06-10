#include "idt.h"
#include "fb.h"

void interrupt_handler(struct cpu_state cpu, struct stack_state stack, unsigned int interrupt) {

	(void) cpu;
	(void) stack;

	char *msg = "salut";

	switch(interrupt) {
		case 0:
			fb_write(msg);
			break;

	}
}

void init_entry(struct idt_entry *entry, unsigned int *function, unsigned short position) {

	(void) position;

	entry->offset_1 = *function & 0xFF00;
	entry->offset_2 = *function & 0x00FF;
	entry->zero = 0;
	entry->selector = 0;
}
