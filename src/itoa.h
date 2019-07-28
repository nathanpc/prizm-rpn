/**
 * itoa.h
 * A simple wrapper to suppress the warnings when using the retarded itoa
 * syscall that takes a unsigned char instead of a char.
 *
 * @author: Nathan Campos <nathan@innoveworkshop.com>
 */

#ifndef _ITOA_H_
#define _ITOA_H_

#include <fxcg/misc.h>

void _itoa(int value, char *buf);

#endif /* _ITOA_H_ */
