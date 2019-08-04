/**
 * operations.c
 * Performs stack operations.
 *
 * @author: Nathan Campos <nathan@innoveworkshop.com>
 */

#include "operations.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
//#include <math.h>
#include <fdlibm.h>
#include "stack.h"
#include "msgbox.h"

// Private methods.
bool check_args(stack_t *stack, int8_t min);


/**
 * Duplicates the last item on the stack.
 * 
 * @param  stack Stack structure.
 * @return       TRUE if the operation was successful.
 */
bool dup(stack_t *stack) {
	if ((*stack).count > 0) {
		stack_push(stack, stack->array[stack->count - 1]);
		return true;
	} else {
		msgbox_show("Nothing on stack\nto duplicate.");
		return false;
	}
}

/**
 * Adds two numbers.
 * 
 * @param  stack Stack structure.
 * @return       TRUE if the operation was successful.
 */
bool add(stack_t *stack) {
	if (check_args(stack, 2)) {
		long double n1 = stack_pop(stack);
		long double n2 = stack_pop(stack);
		stack_push(stack, n2 + n1);
		
		return true;
	}
	
	return false;
}

/**
 * Subtracts two numbers.
 * 
 * @param  stack Stack structure.
 * @return       TRUE if the operation was successful.
 */
bool subtract(stack_t *stack) {
	if (check_args(stack, 2)) {
		long double n1 = stack_pop(stack);
		long double n2 = stack_pop(stack);
		stack_push(stack, n2 - n1);
		
		return true;
	}
	
	return false;
}

/**
 * Multiplies two numbers.
 * 
 * @param  stack Stack structure.
 * @return       TRUE if the operation was successful.
 */
bool multiply(stack_t *stack) {
	if (check_args(stack, 2)) {
		long double n1 = stack_pop(stack);
		long double n2 = stack_pop(stack);
		stack_push(stack, n2 * n1);
		
		return true;
	}
	
	return false;
}

/**
 * Divides two numbers.
 * 
 * @param  stack Stack structure.
 * @return       TRUE if the operation was successful.
 */
bool divide(stack_t *stack) {
	if (check_args(stack, 2)) {
		long double n1 = stack_pop(stack);
		long double n2 = stack_pop(stack);
		stack_push(stack, n2 / n1);
		
		return true;
	}
	
	return false;
}

/**
 * Powers two numbers.
 * 
 * @param  stack Stack structure.
 * @return       TRUE if the operation was successful.
 */
bool _pow(stack_t *stack) {
	if (check_args(stack, 2)) {
		long double n1 = stack_pop(stack);
		long double n2 = stack_pop(stack);
		stack_push(stack, pow(n2, n1));
		
		return true;
	}
	
	return false;
}

/**
 * Squares a number.
 * 
 * @param  stack Stack structure.
 * @return       TRUE if the operation was successful.
 */
bool square(stack_t *stack) {
	if (check_args(stack, 2)) {
		long double n1 = stack_pop(stack);
		stack_push(stack, pow(n1, 2));
		
		return true;
	}
	
	return false;
}

/**
 * Logarithm of a number.
 * 
 * @param  stack Stack structure.
 * @return       TRUE if the operation was successful.
 */
bool _log(stack_t *stack) {
	if (check_args(stack, 2)) {
		long double n1 = stack_pop(stack);
		stack_push(stack, log(n1));
		
		return true;
	}
	
	return false;
}

/**
 * Logarithm of a number on a base of X.
 * 
 * @param  stack Stack structure.
 * @return       TRUE if the operation was successful.
 */
bool logx(stack_t *stack) {
	if (check_args(stack, 2)) {
		long double n1 = stack_pop(stack);
		long double n2 = stack_pop(stack);
		stack_push(stack, log(n2) / log(n1));
		
		return true;
	}
	
	return false;
}

/**
 * Natural logarithm of a number.
 * 
 * @param  stack Stack structure.
 * @return       TRUE if the operation was successful.
 */
bool ln(stack_t *stack) {
	if (check_args(stack, 2)) {
		long double n1 = stack_pop(stack);
		stack_push(stack, log(n1) / log(M_E));
		
		return true;
	}
	
	return false;
}

/**
 * Sine of a number.
 * 
 * @param  stack Stack structure.
 * @return       TRUE if the operation was successful.
 */
bool _sin(stack_t *stack) {
	if (check_args(stack, 2)) {
		long double n1 = stack_pop(stack);
		stack_push(stack, sin(n1));
		
		return true;
	}
	
	return false;
}

/**
 * Cosine of a number.
 * 
 * @param  stack Stack structure.
 * @return       TRUE if the operation was successful.
 */
bool _cos(stack_t *stack) {
	if (check_args(stack, 2)) {
		long double n1 = stack_pop(stack);
		stack_push(stack, cos(n1));
		
		return true;
	}
	
	return false;
}

/**
 * Tangent of a number.
 * 
 * @param  stack Stack structure.
 * @return       TRUE if the operation was successful.
 */
bool _tan(stack_t *stack) {
	if (check_args(stack, 2)) {
		long double n1 = stack_pop(stack);
		stack_push(stack, sin(n1) / cos(n1));
		
		return true;
	}
	
	return false;
}

/**
 * Negate a number.
 * 
 * @param  stack Stack structure.
 * @return       TRUE if the operation was successful.
 */
bool neg(stack_t *stack) {
	if (check_args(stack, 1)) {
		long double n1 = stack_pop(stack);
		stack_push(stack, n1 * -1);
		
		return true;
	}
	
	return false;
}

/**
 * Check if the stack has the minimum number of arguments for a operation.
 * 
 * @param  stack Stack structure.
 * @param  min   Minimum number of arguments.
 * @return       TRUE if there are enough arguments.
 */
bool check_args(stack_t *stack, int8_t min) {
	if ((*stack).count >= min) {
		return true;
	} else {
		msgbox_show("Not enough \narguments.");
		return false;
	}
}
