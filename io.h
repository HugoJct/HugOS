#ifndef IO_H
#define IO_H

/*
 * Sends the given data to the given IO port. Define in io.s
 *
 * @param port The I/O port to sens the data to
 * @param data The data to sens to the port
 * @return void
 */
void outb(unsigned short port, unsigned char data);

#endif
