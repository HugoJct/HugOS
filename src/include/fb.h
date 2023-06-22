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

/** fb_info:
 *
 * Writes a white message on the screen
 *
 * @param msg	The message to display
 */
void fb_info(char *msg);

/** fb_success:
 *
 * Writes a green message on the screen
 *
 * @param msg	The message to display
 */
void fb_success(char *msg);

/** fb_error:
 *
 * Writes a red message on the screen
 *
 * @param msg	The message to display
 */
void fb_error(char *msg);

#endif
