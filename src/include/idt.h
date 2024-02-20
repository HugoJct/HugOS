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

    /*general use registers*/
	unsigned int eax;
	unsigned int ecx;
	unsigned int edx;
	unsigned int ebx;

    /*top stack*/
    unsigned int esp;
	/*bottom stack*/
    unsigned int ebp;

    /*source index*/
    unsigned int esi;
    /*dest index*/
	unsigned int edi;
} __attribute__((packed));

struct stack_state {

	unsigned int error_code;
	/*addr next instruction*/
    unsigned int eip;
    /*code segment index*/
	unsigned int cs;
	unsigned int eflags;
} __attribute__((packed));

struct idtr_t {
	unsigned short size;
	unsigned int address;
} __attribute__((packed)) ;

/* =============== */
/* =====idt.s===== */
/* =============== */

/** load_idt:
 *
 * Loads the provided Interrupt Descriptor Table in memory
 *
 * @param addr: 	The address of the IDT to load
 */
void load_idt(struct idtr_t *addr);

/* ============== */
/* =interrupts.c= */
/* ============== */

/** idt_interrupt_handler:
 *
 * The function that is called when an interruption occurs
 *
 * @param cpu:		The CPU registers values before interruption
 * @param interrupt:	The number of the interrupt
 * @param stack:	The state of the stack before the interruption
 */
void idt_interrupt_handler(struct cpu_state cpu, unsigned int interrupt, struct stack_state stack);

/** idt_init:
 *
 * Initializes the IDT
 */
void idt_init();

#endif
