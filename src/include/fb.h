#ifndef FB_H
#define FB_H

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
