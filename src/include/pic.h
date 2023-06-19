#ifndef PIC_H
#define PIC_H

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28
#define PIC2_END_INTERRUPT (PIC2_START_INTERRUPT + 7)

#define PIC_ACK		0x20		/* End-of-interrupt command code */

#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

#define PIC_TIMER_INT 		0
#define PIC_KEYBOARD_INT 	1
#define PIC_PIC2_INT 		2
#define PIC_COM2_INT		3
#define PIC_COM1_INT		4
#define PIC_LPT2_INT		5
#define PIC_FLOPPY_INT		6
#define PIC_LPT1_INT		7
#define PIC_CLOCK_INT		8
#define PIC_IO1_INT		9
#define PIC_IO2_INT		10
#define PIC_IO3_INT		11
#define PIC_IO4_INT		12
#define PIC_COPROC_INT		13
#define PIC_IDE_1		14
#define PIC_IDE_2 		15

/**
 * Masks the provided interrupt (masked interrupts are not notified to the kernel)
 *
 *  @param interrupt_number:	The interrupt to mask
 */
void PIC_mask_interrupt(unsigned char interrupt_number);

/**
 * Unmasks the provided interrupt
 *
 *  @param interrupt_number:	The interrupt to unmask
 */
void PIC_unmask_interrupt(unsigned char interrupt_number);

/**
 * Remaps the PIC's interrupt numbers to begin at 32 to prevent conflicts with CPU interrupts
 *
 * @param offset1:	The offset for the first PIC
 * @param offset2:	The offset for the second PIC
 */
void pic_remap(int offset1, int offset2);

/** pic_acknowledge:
 * Acknowledges an interrupt from either PIC 1 or PIC 2.
 *
 * @param num The number of the interrupt
 */
void pic_acknowledge(unsigned int interrupt);

#endif
