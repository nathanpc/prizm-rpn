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
bool stack_push_str(stack_t *stack, const char *str);

#endif /* _STACK_H_ */
