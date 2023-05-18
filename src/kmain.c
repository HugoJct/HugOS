#include "io.h"

int kmain(void) {

	char *str = "Hello World !\nHow are you doing today ?";

	fb_clear();
	fb_set_color(FB_GREEN, FB_BLACK);
	fb_write(str);

	return 0;
}
