#include "gdt.h"

uint64_t _gdt[3];

void gdt_init_desc(uint64_t *desc, uint32_t base, uint32_t limit, uint16_t flag) {

	uint64_t descriptor;

	// Create the high 32 bit segment
	descriptor =  limit       & 0x000F0000;         // set limit bits 19:16
	descriptor |= (flag <<  8) & 0x00F0FF00;         // set type, p, dpl, s, g, d/b, l and avl fields
	descriptor |= (base >> 16) & 0x000000FF;         // set base bits 23:16
	descriptor |=  base        & 0xFF000000;         // set base bits 31:24

	// Shift by 32 to allow for low part of segment
	descriptor <<= 32;

	// Create the low 32 bit segment
	descriptor |= base  << 16;                       // set base bits 15:0
	descriptor |= limit  & 0x0000FFFF;

	*desc = descriptor;

}

void gdt_init() {

	struct gdt new_gdt;

	gdt_init_desc(&_gdt[0], 0, 0x000FFFFF, 0);
	gdt_init_desc(&_gdt[1], 0, 0x000FFFFF, GDT_CODE_PL0);
	gdt_init_desc(&_gdt[2], 0, 0x000FFFFF, GDT_DATA_PL0);

	new_gdt.size = sizeof(uint64_t) * 3 - 1;
	new_gdt.address = (unsigned int) _gdt;

	load_gdt(&new_gdt);
	gdt_init_reg();
}

