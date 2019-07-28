/**
 * stack.c
 * RPN stack display and manipulation.
 *
 * @author: Nathan Campos <nathan@innoveworkshop.com>
 */

#include "stack.h"

#include <stdio.h>
#include <stdbool.h>
#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/heap.h>
#include <fxcg/misc.h>
#include "fpconv.h"


/**
 * Initializes the stack structure.
 * 
 * @param stack Stack structure.
 */
void stack_init(stack_t *stack) {
	stack->count = 0;
	//stack->array = (long double*)sys_malloc(sizeof(long double));
}

/**
 * Displays the stack on screen and handles all of the key presses.
 * 
 * @param stack Stack structure.
 */
void stack_show(stack_t *stack) {
	int key;
	int curch;
	char line[DISPLAY_MAX_X_CHARS];
	char numstr[25];

	while (true) {
		// Clear the screen.
		Bdisp_AllClr_VRAM();
		DisplayStatusArea();
		
		// Show stack items.
		for (int i = 0; i < DISPLAY_MAX_LINES; i++) {
			curch = 0;
			
			// Append garbage characters.
			line[curch++] = ' ';
			line[curch++] = ' ';
			
			// Append stack number.
			itoa(i, line + 2);
			
			// Append : and space.
			for (int j = curch; j < DISPLAY_MAX_X_CHARS; j++) {
				if (line[j] == '\0') {
					curch = j;
					
					line[curch++] = ':';
					line[curch++] = ' ';
					line[curch++] = '\0';
					
					break;
				}
			}
			
			// Check if it is a empty or populated stack position.
			if (i < (*stack).count) {
				// Convert number to string.
				int strlen = fpconv_dtoa((*stack).array[i], numstr);
				numstr[strlen] = '\0';
				curch--;
				
				// Append the number to the line string with a fixed precision.
				int aftercomma = strlen;
				for (int j = 0; j < (DISPLAY_MAX_X_CHARS - curch); j++) {
					// Check if we reached the end already.
					if (numstr[j] == '\0') {
						break;
					} else if ((j - aftercomma) > FLOAT_PRECISION) {
						break;
					}
					
					line[curch++] = numstr[j];
					
					// Start counting the fixed precision.
					if ((numstr[j] == '.') && (j < aftercomma)) {
						aftercomma = j;
					}
				}
				
				// Finish the line string.
				line[curch++] = '\0';
			}
			
			// Display the stack line.
			PrintXY(1, DISPLAY_MAX_LINES - i, line,
					TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
		}
		
		// Wait until a key is pressed.
		GetKey(&key);
		
		// Do something with the key press.
		switch (key) {
		case KEY_CTRL_EXE:
			break;
		case KEY_CTRL_EXIT:
			Bdisp_AllClr_VRAM();
			break;
		case KEY_CTRL_UP:
			break;
		case KEY_CTRL_DOWN:
			break;
		}
	}
}

/**
 * Pushes a number into the stack.
 * 
 * @param  stack Stack structure.
 * @param  num   Number to be pushed into the stack.
 * @return       Number index in the stack.
 */
int stack_push(stack_t *stack, const long double num) {
	// Reallocate the memory and append the item to it.
	stack->array = sys_realloc(stack->array,
							   sizeof(long double) * (stack->count + 1));
	stack->array[stack->count++] = num;

	// Return the item index.
	return stack->count - 1;
}

/**
 * Pops a number from the stack.
 * 
 * @param  stack Stack structure.
 * @return       Number that was popped from the stack.
 */
long double stack_pop(stack_t *stack) {
	// Check if there's anything in the stack to be popped.
	if ((*stack).count == 0) {
		// TODO: Show a error message.
		return 0;
	}
	
	stack->count--;
	return 0;
}

