#ifndef TERM_UTILS_H
#define TERM_UTILS_H 
#include "term_vars.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "term_defines.h"
#include "list.h"
#include "term_cmd_line.h"
/* Exits the program */
void exit_program(int opcode);

/* Clears the memory buffer */
void empty_buffer();

/* Resets the term, clearing buffers and whatnot */
void reset_term();

char* trim(char* toTrim);

char** paramListToArray(CommandLine* cmdLine);
#endif // TERM_UTILS_H