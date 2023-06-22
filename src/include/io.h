#ifndef IO_H
#define IO_H

/** outb:
 *
 * Sends the given data to the given IO port.
 *
 * @param port 	The I/O port to sens the data to
 * @param data 	The data to sens to the port
 */
void outb(unsigned short port, unsigned char data);

/** inb:
 *
 * Read a byte from an I/O port.
 *
 * @param port The address of the I/O port
 * @return The read byte
 */
unsigned char inb(unsigned short port);

#endif
