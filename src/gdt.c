#include "gdt.h"

static struct segment_descriptor _gdt[3];
static struct gdt gdt;

void gdt_init_desc(struct segment_descriptor *desc, unsigned int privilege_level, unsigned int type, unsigned int executable, unsigned int readable, unsigned int writable, unsigned int base, unsigned int limit) {

	//p
	desc->access = 1<<7;

	//dpl
	desc->access |= privilege_level << 5;

	//s
	desc->access |= type<<4;

	//e
	desc->access |= executable << 3;

	//rw 
	if(desc->access & (1<<4)) {	//if not system segment

		if(desc->access & (1<<3)) {	//if code segment

			desc->access |= readable<<1;
		} else { 		//data segment

			desc->access |= writable<<1;
		}
	}

	desc->base_high = base & 0xFF000000;
	desc->base_middle |= base & 0x00FF0000;
	desc->base_low |= base & 0x0000FFFF;

	desc->limit_high = limit & 0xF0000000;
	desc->limit_low |= limit & 0x0FFFFFFF;
}

void gdt_init() {

	gdt_init_desc(&_gdt[0], 0, 0, 0, 0, 0, 0, 0);
	gdt_init_desc(&_gdt[1], 0, 1, 1, 1, 1, 0, 0xFFFFFFFF);
	gdt_init_desc(&_gdt[1], 0, 1, 0, 0, 1, 1, 0xFFFFFFFF);

	gdt.size = sizeof(struct segment_descriptor) * 3 - 1;
	gdt.address = (unsigned int) _gdt;

	load_gdt(&gdt);
}

