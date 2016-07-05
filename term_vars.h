#ifndef TERM_VARS_H
#define TERM_VARS_H
#include "term_defines.h"
//  Buffer that holds the characters received 
//  in the terminal
char buffer[BUFFER_SIZE * BUFFER_SIZE]; 
int cursorPos;					// Current position of the cursor 
int currentLinePos;			// Current position of the line-end
int historyPos;					// Current position in the history				

#endif // TERM_VARS_H 