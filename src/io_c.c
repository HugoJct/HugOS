#include "io.h"

static unsigned int cursor_pos = 0;
static unsigned char fg_color = FB_WHITE;
static unsigned char bg_color = FB_BLACK;

void fb_write_char(unsigned int i, char c, unsigned char fg, unsigned char bg) {

	char *fb = (char *) 0x000B8000;

	fb[i * 2] = c;
	fb[(i * 2) + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

void fb_move_cursor(unsigned short pos) {

	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT, pos & 0x00FF);
}

void fb_set_color(unsigned char fg, unsigned char bg) {
	
	fg_color = fg;
	bg_color = bg;
}

void fb_clear(void) {

	for(unsigned int i = 0; i < (80 * 25); i++) {
		fb_write_char(i, ' ', fg_color, bg_color);
	}
}

int fb_write(char *buf) {

	while(*buf != 0) {

		switch(*buf) {
			case '\n':
				cursor_pos += 80 - (cursor_pos % 80) - 1;
				break;
			case '\t':
				cursor_pos += 4;
				break;
			default:
				fb_write_char(cursor_pos, *buf, fg_color, bg_color);
		}

		cursor_pos += 1;
		fb_move_cursor(cursor_pos);

		buf++;
	}

	return 0;
}
