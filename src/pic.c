#include "pic.h"
#include "io.h"

void pic_remap(int offset1, int offset2) {

	unsigned char a1, a2;

	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)

	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

	outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset

	outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset

	outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)

	outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)


	outb(PIC1_DATA, ICW4_8086);               // ICW4: have the PICs use 8086 mode (and not 8080 mode)

	outb(PIC2_DATA, ICW4_8086);


	outb(PIC1_DATA, a1);   // restore saved masks.
	outb(PIC2_DATA, a2);
}

/** pic_acknowledge:
 * Acknowledges an interrupt from either PIC 1 or PIC 2.
 *
 * @param num The number of the interrupt
 */
void pic_acknowledge(unsigned int interrupt) {

	if (interrupt < PIC1_START_INTERRUPT || interrupt > PIC2_END_INTERRUPT) {

		return;
	}

	if (interrupt < PIC2_START_INTERRUPT) {

		outb(PIC1, PIC_EOI);
	} else {

		outb(PIC2, PIC_EOI);
	}
}
