/**
 * RPN Calculator
 * A add-in to transform your Casio Prizm into a much more powerful calculator.
 *
 * @author Nathan Campos <nathan@innovewokshop.com>
 */

#include <stdbool.h>
#include <fxcg/display.h>
#include "stack.h"
#include "msgbox.h"


int main() {
	// Initialize the screen for our add-in.
    Bdisp_EnableColor(true);
    Bdisp_AllClr_VRAM();
	EnableStatusArea(2);

	// Prepare the stack.
	stack_t stack;
	stack_init(&stack);
	stack_push(&stack, 1.23456789L);
	stack_push(&stack, 2.3456789L);
	stack_push(&stack, 3.456789L);
	
	// Display the stack and start the event loop.
	stack_show(&stack);
	
	return 0;
}
