#ifndef IDT_H
#define IDT_H

#include "stdint.h"

struct idt_entry {

	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t     reserved;     // Set to zero
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed));

struct cpu_state {

	unsigned int eax;
	unsigned int ecx;
	unsigned int edx;
	unsigned int ebx;
	unsigned int esp;
	unsigned int ebp;
	unsigned int esi;
	unsigned int edi;
} __attribute__((packed));

struct stack_state {

	unsigned int error_code;
	unsigned int eip;
	unsigned int cs;
	unsigned int eflags;
} __attribute__((packed));

struct idtr_t {
	unsigned short size;
	unsigned int address;
} __attribute__((packed)) ;

void load_idt(struct idtr_t *addr);

void idt_init();

#endif
