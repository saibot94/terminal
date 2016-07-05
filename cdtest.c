#include "term_commands.h"
#include "term_defines.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



char** tokenizeCommand(char* str, int* size)
{
	char* string;
	char** arr;
	char buf[ARGSIZE +1 ];
	int j, i = 0;
	arr = malloc(sizeof(char*) * ARGSIZE);
	memset(arr, 0, ARGSIZE);
	string = strtok(str, " ");
	while(string != NULL)
	{
		//strcat(string, "\0");
		arr[i] = malloc(sizeof(char) * ARGSIZE);
		strcpy(arr[i], string);
		string = strtok(NULL, " ");
		i++;
	}
	arr[i] = NULL;
	*size = i;
	return arr;
}

int main(int argc, char const *argv[])
{
	char buf[256];
	int size;
	while(1)
	{
		printf("$> ");
		fgets(buf,255,stdin);
		char** command = tokenizeCommand(buf, &size);
		if(strncmp(command[0],"cd",2) == 0)
		{
			cd(size, command);
		}
		else if(strcmp(command[0],"ls") == 0)
		{
			
			//	execvp(command[0],command);
			
		}
	}
	return 0;
}