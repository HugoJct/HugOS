#include "io.h"
#include "keyboard.h"
#include "stdbool.h"
#include "fb.h"

static bool pressed = false;

static char layout[] = {
	' ', ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ')', '=', 0x08,
	'\t', 'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$', '\n',
	0x08, 'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', '%', '*',
       	0x00, '<', 'w', 'x', 'c', 'v', 'b', 'n', ',', ';', ':', '!'
};

/** read_scan_code:
 * Reads a scan code from the keyboard
 *
 * @return The scan code (NOT an ASCII character!)
 */
static unsigned char read_scan_code(void) {

	return inb(KBD_DATA_PORT);
}

static char scan_code_to_ascii(unsigned char code) {
	return layout[code];
}

static unsigned char read_ascii() {
	unsigned char scan_code = read_scan_code();
	return scan_code_to_ascii(scan_code);	
}

void keyboard_handle_interruption() {

	if(pressed) {
		pressed = !pressed;
		read_ascii();
		return;
	} else {
		pressed = !pressed;

		char c = read_ascii();
		char str[2] = {
			c,
			(char) 0
		};
		fb_info(str);
	}
}
