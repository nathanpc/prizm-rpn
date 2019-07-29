/**
 * stack.c
 * RPN stack display and manipulation.
 *
 * @author: Nathan Campos <nathan@innoveworkshop.com>
 */

#include "stack.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/heap.h>
#include <fxcg/misc.h>
#include "fpconv.h"
#include "itoa.h"

// Private methods.
void clear_line(char *line);
void append_char(char *str, const char c);
void show_stack_lines(const stack_t stack, const bool input_line);


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
	bool in_exp = false;
	char input_line[DISPLAY_MAX_X_CHARS];
	clear_line(input_line);

	while (true) {
		// Clear the screen.
		Bdisp_AllClr_VRAM();
		DisplayStatusArea();
		
		// Show stack items.
		show_stack_lines(*stack, input_line[2] != '\0');
		
		// Show input line.
		if (input_line[2] != '\0') {
			PrintXY(1, DISPLAY_MAX_LINES, input_line,
					TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
		}
		
		// Wait until a key is pressed.
		GetKey(&key);
		
		// Do something with the key press.
		switch (key) {
		case KEY_CTRL_EXE:
			if (input_line[2] == '\0') {
				// DUP
				if ((*stack).count > 0) {
					stack_push(stack, stack->array[stack->count - 1]);
				} else {
					// TODO: Show error.
				}
			} else {
				// Push the number to the stack.
				if (stack_push_str(stack, input_line + 2)) {
					clear_line(input_line);
				}
			}
			
			in_exp = false;
			break;
		case KEY_CTRL_DEL:
			stack_pop(stack);
			in_exp = false;
			break;
		case KEY_CTRL_AC:
			clear_line(input_line);
			in_exp = false;
			break;
		case KEY_CTRL_EXIT:
			Bdisp_AllClr_VRAM();
			in_exp = false;
			break;
		case KEY_CHAR_0:
		case KEY_CHAR_1:
		case KEY_CHAR_2:
		case KEY_CHAR_3:
		case KEY_CHAR_4:
		case KEY_CHAR_5:
		case KEY_CHAR_6:
		case KEY_CHAR_7:
		case KEY_CHAR_8:
		case KEY_CHAR_9:
		case KEY_CHAR_DP:
			// Append number to string.
			append_char(input_line, key);
			break;
		case KEY_CHAR_EXP:
			append_char(input_line, 'E');
			in_exp = true;
			break;
		case KEY_CHAR_PMINUS:
			if (in_exp) {
				// Inserting a minus inside a EXP.
				append_char(input_line, '-');
			} else {
				// Invert the current input number.
				// TODO: Push to the stack and then INV.
			}
			break;
		}
	}
}

/**
 * Show the stack lines on screen.
 * 
 * @param stack      Stack structure.
 * @param input_line Leave a blank line at the bottom for user input?
 */
void show_stack_lines(const stack_t stack, const bool input_line) {
	int8_t curch;
	char line[DISPLAY_MAX_X_CHARS];
	char numstr[25];
	int8_t max_lines =  DISPLAY_MAX_LINES;
	
	// If the input line is active then remove one of the stack lines.
	if (input_line) {
		max_lines--;
	}

	// Display each line.
	for (int8_t i = 0; i < max_lines; i++) {
		curch = 0;
			
		// Append garbage characters.
		line[curch++] = ' ';
		line[curch++] = ' ';
		
		// Append stack number.
		_itoa(i, line + 2);
			
		// Append : and space.
		for (int8_t j = curch; j < DISPLAY_MAX_X_CHARS; j++) {
			// Check where the int to string conversion has left us.
			if (line[j] == '\0') {
				// Update counter.
				curch = j;
					
				// Append colon and space separator.
				line[curch++] = ':';
				line[curch++] = ' ';
				line[curch++] = '\0';
					
				break;
			}
		}
			
		// Check if it is a empty or populated stack position.
		if (i < stack.count) {
			// Convert number to string.
			int8_t strlen = fpconv_dtoa(stack.array[i], numstr);
			numstr[strlen] = '\0';
			curch--;
				
			// Append the number to the line string with a fixed precision.
			int8_t aftercomma = strlen;
			for (int8_t j = 0; j < (DISPLAY_MAX_X_CHARS - curch); j++) {
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
		if (input_line) {
			PrintXY(1, DISPLAY_MAX_LINES - i - 1, line,
					TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
		} else {
			PrintXY(1, DISPLAY_MAX_LINES - i, line,
					TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
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
int8_t stack_push(stack_t *stack, const long double num) {
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
	
	stack->array = sys_realloc(stack->array,
							   sizeof(long double) * (stack->count - 1));
	stack->count--;
	return 0;
}

/**
 * Converts a string to a number and pushes it to the stack.
 * 
 * @param  stack Stack structure.
 * @param  str   Number string.
 * @return       TRUE if the conversion went well.
 */
bool stack_push_str(stack_t *stack, const char *str) {
	char *endptr;
	double n = strtod(str, &endptr);
	
	// Check for conversion errors.
	if ((n == 0.0L) && (str == endptr)) {
		// TODO: Error, invalid number.
		stack_push(stack, 0.321L);
		return false;
	} else if (errno == ERANGE) {
		// TODO: Number way too big.
		return false;
	}
	
	stack_push(stack, n);
	return true;
}

/**
 * Append a single character to the end of a string.
 * 
 * @param str String to be manipulated.
 * @param c   Character to be appended.
 */
void append_char(char *str, const char c) {
	for (uint8_t i = 0; i < DISPLAY_MAX_X_CHARS; i++) {
		if (str[i] == '\0') {
			str[i] = c;
			str[i + 1] = '\0';
			break;
		}
	}
}

/**
 * Clears a line string.
 * 
 * @param line Line string to be cleared.
 */
void clear_line(char *line) {
	line[0] = ' ';
	line[1] = ' ';
	line[2] = '\0';
}
