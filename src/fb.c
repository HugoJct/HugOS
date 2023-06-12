#include "fb.h"
#include "io.h"
#include "gdt.h"
#include "stdbool.h"

static bool init = true;
static unsigned int cursor_pos = 0;
static unsigned char fg_color = FB_WHITE;
static unsigned char bg_color = FB_BLACK;

/**
 * Writes the specified character at the specified offset
 *
 * @param pos 	The position at which to prints the character 
 * @param c 	The character to display
 * @param fg 	The foreground color of the character
 * @param bg 	The background color of the character
 */
static void fb_write_char(unsigned int i, char c, unsigned char fg, unsigned char bg) {

	char *fb = (char *) 0x000B8000;

	fb[i * 2] = c;
	fb[(i * 2) + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

/**
 * Moves the cursor of the framebuffer to the given position
 *
 * @param pos 	The new position of the cursor
 */
static void fb_move_cursor(unsigned short pos) {

	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT, pos & 0x00FF);
}

/**
 * Sets the colors the framebuffer
 *
 * @param fg 	The Foreground color
 * @param bg	The Background color
 */
static void fb_set_color(unsigned char fg, unsigned char bg) {
	
	fg_color = fg;
	bg_color = bg;
}

/**
 * Clears the screen
 */
static void fb_clear(void) {

	for(unsigned int i = 0; i < (80 * 25); i++) {
		fb_write_char(i, ' ', fg_color, bg_color);
	}
}


/**
 * Prints the given string to the screen
 *
 * @param buf	The string to display
 */
int fb_write(char *buf) {

	if(init) {
		fb_clear();
		init = false;
	}

	while(*buf != 0) {

		switch(*buf) {
			case '\n':
				cursor_pos += 80 - (cursor_pos % 80) - 1;
				break;
			case '\t':
				cursor_pos += 4;
				break;
			case '\r':
				cursor_pos -= (cursor_pos % 80) + 1;
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

void fb_info(char *msg) {
	
	fb_set_color(FB_LIGHT_GREY, FB_BLACK);
	fb_write(msg);
	fb_write("\n");
}

void fb_success(char *msg) {
	
	fb_set_color(FB_GREEN, FB_BLACK);
	fb_write(msg);
	fb_write("\n");
}

void fb_error(char *msg) {
	
	fb_set_color(FB_RED, FB_BLACK);
	fb_write(msg);
	fb_write("\n");
}

