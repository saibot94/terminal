/* Command line data structure */
#ifndef CMD_LINE_H
#define CMD_LINE_H 

#include "list.h"

typedef struct CommandLine 
{
	char *command;
	char *inFile;
	char *outFile;
	int pipedIn;
	int pipedOut;
	List *params;
} CommandLine;

#endif

