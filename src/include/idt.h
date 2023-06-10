#ifndef IDT_H
#define IDT_H

#include "stdint.h"

struct idt_entry{

	uint16_t offset_1;        // offset bits 0..15
	uint8_t  zero;            // unused, set to 0
	uint8_t  type_attributes; // gate type, dpl, and p fields
	uint16_t selector;        // a code segment selector in GDT or LDT
	uint16_t offset_2; 
} __attribute__((packed)) ;

struct cpu_state{

	unsigned int eax;
	unsigned int ecx;
	unsigned int edx;
	unsigned int ebx;
	unsigned int esp;
	unsigned int ebp;
	unsigned int esi;
	unsigned int edi;
} __attribute__((packed));

struct stack_state{

	unsigned int error_code;
	unsigned int eip;
	unsigned int cs;
	unsigned int eflags;
} __attribute__((packed)) ;

void interrupt_handler(struct cpu_state cpu, struct stack_state stack, unsigned int interrupt);
void init_entry(struct idt_entry *entry, unsigned int *function, unsigned short position);

extern void load_idt(unsigned int *addr);
extern void interrupt_handler_0(void);

#endif
