#ifndef TERM_TEXTED_H
#define TERM_TEXTED_H 
#include "stdafx.h"
#include "term_exec.h"
#include "term_utils.h"
#include "term_history.h"
#include "term_commands.h"
#include "list.h"

/* Shifts the command line characters from the 
	current position to the right one character */
void shiftBufferPosRight();

/* Shifts the command line characters from the 
	current position to the left one character */
void shiftBufferPosLeft();

/* Redraws current line on screen */
void redrawLine();

/* Removes everything on the current line */
void deleteLine();

/* Handles the current char on screen */
void handleCharacter(char c);

/* Handles a backspace */
void handleBackspace();

/* Checks if the buffer contains any relevant data */
int isEmpty(char* buffer);
#endif