#ifndef GDT_H
#define GDT_H

#include "stdint.h"

struct segment_descriptor {

	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	unsigned short limit_high;
	unsigned short flags;
	uint8_t base_high;
} __attribute__((packed));

struct gdt {

	unsigned int address;
	unsigned short size;
} __attribute__((packed));

/**
 *	gdt.c
 */
void gdt_init_desc(struct segment_descriptor *desc, unsigned int privilege_level, unsigned int type, unsigned int executable, unsigned int readable, unsigned int writable, unsigned int base, unsigned int limit);
void gdt_init(void);

/**
 *	lgdt.s
 */
void load_gdt(struct gdt *table);

#endif
