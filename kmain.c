#include "io.h"

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5

#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15


/** fb_move_cursor:
 * Moves the cursor of the framebuffer to the given position
 *
 * @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos) {

	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT, pos & 0x00FF);
}

void fb_write_char(unsigned int i, char c, unsigned char fg, unsigned char bg) {
	
	char *fb = (char *) 0x000B8000;

	fb[i * 2] = c;
	fb[(i + 1) * 2] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

int kmain(void) {

	fb_write_char(0, 'H', 15, 0);
	fb_write_char(1, 'e', 15, 0);
	fb_write_char(2, 'l', 15, 0);
	fb_write_char(3, 'l', 15, 0);
	fb_write_char(4, 'o', 15, 0);
	fb_write_char(5, ' ', 15, 0);
	fb_write_char(6, 'W', 15, 0);
	fb_write_char(7, 'o', 15, 0);
	fb_write_char(8, 'r', 15, 0);
	fb_write_char(9, 'l', 15, 0);
	fb_write_char(10, 'd', 15, 0);

	return 0;
}
