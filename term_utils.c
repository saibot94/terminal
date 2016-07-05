#include "term_utils.h"
#include <unistd.h>

void exit_program(int opcode)
{

	printf("\n");
	system("stty sane");
	_exit(0);
}


char** paramListToArray(CommandLine* cmdLine)
{
	char* command = cmdLine->command;
	List* list = cmdLine->params;
	int len = listLength(list)+2;
	int i = 1;

	char** params = (char**)(malloc(sizeof(char*) * len));
	memset(params, 0, len);
	params[0] = command;
	ListNode* node = list->head;
	while(node != NULL)
	{
		params[i++] = (char*)node->item;
		node = node->next;
	}
	params[i] = NULL;
	return params;
}


void empty_buffer()
{	
	memset(buffer, 0, BUFFER_SIZE * BUFFER_SIZE);
}

void reset_term()
{
	empty_buffer();
	cursorPos=0;				
	currentLinePos = 0;		
    historyPos=0;	
	printf("\n");
	redrawLine();
}


char* trim(char* toTrim)
{
	int i,j, cnt = 0;
	char* newString = (char*) malloc(sizeof(char) * strlen(toTrim));
	if(strlen(toTrim) > 2)
	{
		for(i = 0; (toTrim[i] == ' ' || toTrim[i] == '\n')  && i < strlen(toTrim); i++)
		{
			// loop while there's a space at the start
		}
		for(j = strlen(toTrim) - 1; (toTrim[j] == ' ' || toTrim[j] == '\n' || toTrim[j] == '\0') && j >=0 ; j--)
		{
			// loop while there's a space at the end
		}
		if(i <= j)
		{
			for( ; i <=j+1; i++)
			{
				newString[cnt++] = toTrim[i]; 
			}
		}	
		newString[cnt] = '\0';
	}
	else
	{
		return toTrim;
	}

	return newString;
}