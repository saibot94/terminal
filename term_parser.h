#ifndef TERM_CMD_PARSER
#define TERM_CMD_PARSER

#include "term_commands.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "term_defines.h"
#include "list.h"

#include "term_cmd_line.h"
#include "term_utils.h"



/* Parses the command received from the input
	Returns 1 if no command was executed
	Returns 0 if a command was executed
 */
List*    parse_command(char* buffer, int pos);

/* Splits the command line into tokens that are gonna be passed on to the exec functions */
List* tokenizeCommand(char* str, int* size);

/* Checks if CD was called */
int    checkCD(char** arr);

#endif // TERM_CMD_PARSER