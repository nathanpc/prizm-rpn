/**
 * msgbox.c
 * A simple MsgBox wrapper to easily create message boxes.
 *
 * @author: Nathan Campos <nathan@innoveworkshop.com>
 */

#include "msgbox.h"

#include <stdint.h>
#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include "misc.h"

/**
 * Shows a simple message box that can be dismissed by pressing any key.
 * 
 * @param text Text to be displayed inside the box. Accepts newlines.
 */
void msgbox_show(const char *text) {
	uint8_t lines = 1;
	uint8_t strlen = 0;
	uint8_t top_padding = 1;
	
	// Count the number of lines.
	for (uint8_t i = 0; i < 255; i++) {
		if (text[i] == '\0') {
			// Reached the end of the string.
			strlen = i + 1;
			break;
		} else if (text[i] == '\n') {
			// New line found.
			lines++;
		}
	}
	
	// Define the top padding.
	switch (lines) {
	case 1:
		top_padding = 3;
		break;
	case 2:
	case 3:
		top_padding = 2;
		break;
	}
	
	// Display the message box border.
	MsgBoxPush(lines);
	
	// Display the lines.
	uint8_t curline = 1;
	uint8_t lastpos = 0;
	char line[DISPLAY_MAX_X_CHARS];
	line[0] = ' ';
	line[1] = ' ';
	line[2] = '\0';
	for (uint8_t i = 0; i < strlen; i++) {
		// New line or string ending found.
		if ((text[i] == '\n') || (text[i] == '\0')) {
			// Terminate the string.
			line [i + 2 - lastpos] = '\0';
			lastpos = i + 1;
			
			// Print the line.
			PrintXY(3, top_padding + curline++, line,
					TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
		}
		
		// Append character to the line.
		line[i + 2 - lastpos] = text[i];
	}
	
	// Wait for a key press.
	int key;
	GetKey(&key);
	MsgBoxPop();
	
	// Clear the screen.
	Bdisp_AllClr_VRAM();
	DisplayStatusArea();
}

