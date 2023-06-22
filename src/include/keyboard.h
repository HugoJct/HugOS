#ifndef KEYBOARD_H
#define KEYBOARD_h

#define KBD_DATA_PORT 0x60

/** keyboard_handle_interruption:
 *
 * Executes actions when a key is pressed (display the character on screen)
 */
void keyboard_handle_interruption();

#endif
