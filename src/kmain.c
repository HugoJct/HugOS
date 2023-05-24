#include "io.h"
#include "fb.h"

int kmain(void) {

	char *str = "Hello World !\n";

	fb_clear();
	fb_set_color(FB_GREEN, FB_BLACK);
	fb_write(str);

	while(1) {}

	return 0;
}
