#include "gdt.h"
#include "fb.h"

#define GDT_SEGMENTS_COUNT 3

static struct segment_descriptor _gdt_segments[GDT_SEGMENTS_COUNT];
static struct gdt _gdt;

/** gdt_init_desc:
 *
 * Initializes a descriptor with the provided values
 */
static void gdt_init_desc(struct segment_descriptor *desc, uint32_t base, uint32_t limit, uint16_t flag) {

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

	//put values into the segment descriptor
	desc->limit_low = descriptor & 0xFFFF;
	desc->base_low = (descriptor >> 16) & 0xFFFF;
	desc->base_middle = (descriptor >> 32) & 0xFF;
	desc->access = (descriptor >> 40) & 0xFF;
	desc->flags = (descriptor >> 48) & 0xFF;
	desc->base_high = (descriptor >> 56) & 0xFF;
}

void gdt_init() {

	fb_info("[GDT] - Initializing...\n");

	//first segment in array is null
	gdt_init_desc(&_gdt_segments[0], 0, 0, 0);

	//second segment defines code segment for kernel
	gdt_init_desc(&_gdt_segments[1], 0, 0xFFFFFFFF, (GDT_CODE_PL0));

	//third segment defines data segment for kernel
	gdt_init_desc(&_gdt_segments[2], 0, 0xFFFFFFFF, (GDT_DATA_PL0));

	_gdt.size = sizeof(struct segment_descriptor) * GDT_SEGMENTS_COUNT - 1;	// -1 from doc
	_gdt.address = (unsigned int) _gdt_segments;

	fb_success("\tSuccess !\n");

	//load GDT into processor
	fb_info("[GDT] - Loading...\n");
	load_gdt(&_gdt);
	fb_success("\tSuccess !\n");

	//initialize segment registers
	fb_info("[GDT] - Initializing registers...\n");
	gdt_init_reg();
	fb_success("\tSuccess !\n");
}

