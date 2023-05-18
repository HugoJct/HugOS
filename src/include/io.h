#ifndef IO_H
#define IO_H

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5

#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

enum color {
	FB_BLACK,
	FB_BLUE,
	FB_GREEN,
	FB_CYAN,
	FB_RED,
	FB_MAGENTA,
	FB_BROWN,
	FB_LIGHT_GREY,
	FB_DARK_GREY,
	FB_LIGHT_BLUE,
	FB_LIGHT_GREEN,
	FB_LIGHT_CYAN,
	FB_LIGHT_RED,
	FB_LIGHT_MAGENTA,
	FB_LIGHT_BROWN,
	FB_WHITE
};

/*
 * ===========================
 * 	DEFINED IN IO_S.s
 * ===========================
 */

/**
 * Sends the given data to the given IO port.
 *
 * @param port 	The I/O port to sens the data to
 * @param data 	The data to sens to the port
 */
void outb(unsigned short port, unsigned char data);






/*
 * ===========================
 *	DEFINED IO IO_C.c
 * ===========================
 */

/**
 * Writes the specified character at the specified offset
 *
 * @param pos 	The position at which to prints the character 
 * @param c 	The character to display
 * @param fg 	The foreground color of the character
 * @param bg 	The background color of the character
 */
void fb_write_char(unsigned int pos, char c, unsigned char fg, unsigned char bg);

/**
 * Moves the cursor of the framebuffer to the given position
 *
 * @param pos 	The new position of the cursor
 */
void fb_move_cursor(unsigned short pos);

/**
 * Sets the colors the framebuffer
 *
 * @param fg 	The Foreground color
 * @param bg	The Background color
 */
void fb_set_color(unsigned char fg, unsigned char bg);

/**
 * Clears the screen
 */
void fb_clear(void);

/**
 * Prints the given string to the screen
 *
 * @param buf	The string to display
 */
int fb_write(char *buf);

#endif
