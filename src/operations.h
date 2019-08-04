/**
 * operations.h
 * Performs stack operations.
 *
 * @author: Nathan Campos <nathan@innoveworkshop.com>
 */

#ifndef _OPERATIONS_H_
#define _OPERATIONS_H_

#include <stdbool.h>
#include "stack.h"

#define M_E  2.71828182845904523536
#define M_PI 3.14159265358979323846

// Arithmetic operations.
bool add(stack_t *stack);
bool subtract(stack_t *stack);
bool multiply(stack_t *stack);
bool divide(stack_t *stack);
bool _pow(stack_t *stack);
bool square(stack_t *stack);
bool _log(stack_t *stack);
bool logx(stack_t *stack);
bool ln(stack_t *stack);
bool _sin(stack_t *stack);
bool _cos(stack_t *stack);
bool _tan(stack_t *stack);
bool neg(stack_t *stack);

// Stack operations.
bool dup(stack_t *stack);

#endif /* _OPERATIONS_H_ */
