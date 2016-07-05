#include "term_parser.h"


 const char* CL_DELIMS[] = {" ", ">", "<", "|"};
 const int CL_CAN_ADD[] = {  0,   1,   1,   1 };
 const int CL_DELIMS_COUNT = 4;
 const int CL_OPSIZE = 3;

 const char* CL_REDIR_IN = "<";
 const char* CL_REDIR_OUT = ">";
 const char* CL_PIPE = "|";

int checkCD(char** arr)
{
	if(strcmp(arr[0], "cd") == 0)
	{
		return 1;
	}
	return 0;
}


/* Deprecated */
char** old_tokenizeCommand(char* str, int* size)
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

int isDelimiter(char* token)
{
	int i;
	for(i =0; i< CL_DELIMS_COUNT; i++)
	{
		if(strcmp(CL_DELIMS[i],token) == 0)
		{
			return 1;
		}
	}
	return 0;
}


int checkDelimiters(int* index, char* cmdLine, char* string, int *stringSize, List* tokens)
{
	int isDelim = 0;
	int i, j = 0;
	char* tmp;
	int forwardLen = 0;

	for(i = 0; i < CL_DELIMS_COUNT; i++)
	{
		/* Check if current command line has enough space for this delimiter left */
		if((strlen(cmdLine) - (*index)) >= strlen(CL_DELIMS[i]))
		{
			/* Create a temporary buffer for storing the delimiter */
			tmp = (char*)malloc(sizeof(char) * strlen(CL_DELIMS[i] + 1));
			for(j = 0; j < strlen(CL_DELIMS[i]); j++)
			{
				tmp[j] = cmdLine[j+(*index)];
			} 
			tmp[j] = '\0';
			if(strcmp(tmp, CL_DELIMS[i]) == 0)
			{
				string[*stringSize] = '\0';
				if(strlen(string) > 0)
				{
					
					char* copyString = (char*)malloc(sizeof(char) * strlen(string));
					strcpy(copyString, string);
					listInsertBack(tokens, copyString);
					memset(string, 0,(sizeof(char) * ARGSIZE));
					*stringSize = 0;
				}

				forwardLen=strlen(CL_DELIMS[i])-1;
				isDelim = 1;

				if(CL_CAN_ADD[i])
				{
					char* newTmp = trim(tmp);
					//strcpy(newTmp,tmp);
					listInsertBack(tokens, newTmp);
				}
			
				break;
			}
			else
			{
				free(tmp);
			}
		}
	}
	*index += forwardLen;
	return isDelim;
}

List* tokenizeCommand(char* str, int* size)
{
	char* string;
	List* tokens = listCreate();
	int inQuotes = 0, delimiter = 0;
	char buf[ARGSIZE +1 ];
	int j, cnt = 0, i = 0;
	string = malloc(sizeof(char) * ARGSIZE);
	memset(string, 0, ARGSIZE);

	for(i = 0; i < strlen(str); i++)
	{
		delimiter = 0;
		if(str[i] == '\"' || str[i] == '\'')
		{
			inQuotes = !inQuotes;
		}
		else if(!inQuotes)
		{
			delimiter = checkDelimiters(&i, str, string, &cnt, tokens);
			if(!delimiter)
			{
				string[cnt++] = str[i];
			}
		}
		else
		{
			string[cnt++] = str[i];
		}

	}
	if(cnt > 0)
	{
		string[cnt] = '\0';
		listInsertBack(tokens,string);		
	}

	return tokens;
}

CommandLine* createCmdLine(char *command,List *params,char** operators,char** files,int pipeIn,int pipeOut)
{
	int i;
	CommandLine* cmdLine = (CommandLine*) malloc(sizeof(CommandLine));
	
	cmdLine->command = command;
	cmdLine->params = params;
    cmdLine->pipedOut = pipeOut;
    cmdLine->pipedIn = pipeIn;
    /* Get the files now */
	for(i =0; i<CL_OPSIZE; i++)
	{
		if(operators[i] != NULL && files[i] != NULL)
	    {
	    	if(strcmp(operators[i],CL_REDIR_IN) == 0)
	    	{
	    		cmdLine->inFile = files[i];
	    	}
	    	else if(strcmp(operators[i],CL_REDIR_OUT) == 0)
	    	{
	    		cmdLine->outFile = files[i];
	    	}
	    }
	}
		
	return cmdLine;
}

/* Debug purposes function */
void debugCmdLine(CommandLine* cmdLine)
{
	 printf("The command was: %s\n",cmdLine->command );
	 printf("=====================================\n");
	 if(cmdLine->inFile)
	 {

	 	printf("InFile: %s\n", cmdLine->inFile);
	 }
	 if(cmdLine->outFile)
	 {
	 	printf("outFile: %s\n", cmdLine->outFile);
	 }
	 printf("=====================================\n");
	 
	 if(listLength(cmdLine->params) != 0)
	 {
		 printf("The parameters: \n");
		 listPrint(cmdLine->params);
	 }
	 printf("=====================================\n");
	 
	 if(cmdLine->pipedIn)
	 {
	 	printf("This function is piped in!\n");
	 }
	 if(cmdLine->pipedOut)
	 {
	 	printf("This function is piped out!\n");
	 }
}
/* Returns a list of all the commands that have been issued to the terminal */
List* parse_command(char* buffer, int pos)
{
	printf("\n");
	int size,fd[2];
	int i;
	int pipeIn = 0, pipeOut = 0;
	char** operators;
	char** files;
	List* tokens = tokenizeCommand(buffer, &size);
	List* cmdList = listCreate();

	while(listLength(tokens) != 0 )
	{
		/* Get the command first */
		char* command = (char*)listPopHead(tokens);

		/* Get the parameters */
		List* params = listCreate();
		while(listLength(tokens) != 0)
		{
			char* tempStr = (char*)listPeekHead(tokens);
			if(!isDelimiter(tempStr))
			{
				listInsertBack(params,tempStr);
				listPopHead(tokens);
			}
			else
			{
				break;
			}
		}

		/* Check for redirects */
		operators = (char**)malloc(sizeof(char*) * CL_OPSIZE);
		files = (char**) malloc(sizeof(char*) * CL_OPSIZE);
		for(i = 0; i < CL_OPSIZE; i++)
		{
			operators[i] = NULL;
			files[i] = NULL;
		}

		if(listLength(tokens) != 0)
		{
			for(i = 0; (i < CL_OPSIZE) && (listLength(tokens) != 0); i++)
			{
				char* tempStr = (char*) listPeekHead(tokens);
				if(strcmp(tempStr,CL_REDIR_IN) == 0 ||
					strcmp(tempStr,CL_REDIR_OUT) == 0)
				{
					listPopHead(tokens);
					operators[i] = tempStr;
					files[i] = (char*)listPopHead(tokens);
				}
			}
		}

		/* Check for a pipe */
		pipeOut = 0;
		if(listLength(tokens) != 0)
		{
			char* tempStr = (char*) listPeekHead(tokens);
			if(strcmp(tempStr, CL_PIPE) == 0)
			{/* A pipe out was found */
				pipeOut = 1;
				listPopHead(tokens);
			}
		}

		 CommandLine* cmdLine = createCmdLine(command, params, operators, files, pipeIn, pipeOut);
         listInsertBack(cmdList, cmdLine);
         //debugCmdLine(cmdLine);
		
		 pipeIn = pipeOut;
	}
	free(tokens);

	return cmdList;


	/* First we check to see if the cd command was called */
	// if(checkCD(toPass) == 1)
	// {
	// 	cd(size, toPass);
	// }
	// else
	// {		
	// 	pipe(fd);
	// 	if(fork() == 0)
	// 	{	/*Child */
	// 		close(fd[0]);
	// 		dup2(fd[1], 1); // redirect stdout to pipe
	// 		if( execvp(toPass[0], toPass) == -1)
	// 		{
	// 			close(fd[1]);
	// 			printf("No such command: %s", toPass[0]);
	// 			exit(1);
	// 		}			
	// 		return 0;
	// 	}
	// 	else
	// 	{
			// /* Parent */
			// wait(NULL);
			// close(fd[1]);
			// int sz = 32, i, j;
			// char buf[sz];
			// while((i = read(fd[0],buf,sz-1)) > 0)
			// {
			// 	buf[i] ='\0';
			// 	printf("%s",buf );
			// }
			// close(fd[0]);
	// 	}		
	// }

	
	
}