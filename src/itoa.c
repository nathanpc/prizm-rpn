/**
 * itoa.c
 * A simple wrapper to suppress the warnings when using the retarded itoa
 * syscall that takes a unsigned char instead of a char.
 *
 * @author: Nathan Campos <nathan@innoveworkshop.com>
 */

#include "itoa.h"

void _itoa(int value, char *buf) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-sign"
	itoa(value, buf);
#pragma GCC diagnostic pop
}
