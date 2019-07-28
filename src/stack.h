/**
 * stack.h
 * RPN stack display and manipulation.
 *
 * @author: Nathan Campos <nathan@innoveworkshop.com>
 */

#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>
#include <stdint.h>

#define DISPLAY_MAX_LINES   8
#define DISPLAY_MAX_COLUMNS 20
#define DISPLAY_MAX_X_CHARS (DISPLAY_MAX_COLUMNS + 3)
#define FLOAT_PRECISION     5

typedef struct {
	int8_t count;
	long double *array;
} stack_t;


// Display and handling.
void stack_show(stack_t *stack);

// Stack operations.
void stack_init(stack_t *stack);
int8_t stack_push(stack_t *stack, const long double num);
long double stack_pop(stack_t *stack);

#endif /* _STACK_H_ */
