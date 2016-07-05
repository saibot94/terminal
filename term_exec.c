#include "term_exec.h"

/* Parent from the last child to the parent*/

static int finalFd[2];
int pidCount;
int saved_stdout;
int saved_stdin;
	int fd_in, fd_out;


int checkBuiltIn(CommandLine* cmdLine);
void executeCommand(CommandLine* cmdLine, int);
int checkBuiltInParent(CommandLine* cmdLine);
int doRedirects(CommandLine* cmdLine, int);
void waitAllChildren();
void restoreIO();

int checkBuiltInParent(CommandLine* cmdLine)
{
	char* command = cmdLine->command;
	char** arr= paramListToArray(cmdLine);
	int len = listLength(cmdLine->params) + 1;
	if(strcmp(command, "exit") == 0)
	{
		exit_program(0);
	}
	else if (strcmp(command,"cd") == 0)
	{
		cd(len, arr);
		return 1;
	}
	return 0;
}

void waitAllChildren()
{
	int i;
	for(i = 0; i < pidCount; i++)
	{
		wait(&i);
	}
	/* Parent */
	close(finalFd[1]);
	int sz = 32, j;
	char buf[sz];
	while((i = read(finalFd[0],buf,sz-1)) > 0)
	{
		buf[i] ='\0';
		printf("%s",buf );
	}
	close(finalFd[0]);
}


void restoreIO()
{	
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);

	
}

void executeCommandList(List* command_list)
{
	/* Get all the commands one by one */
	int lastCommand = 0;
	pidCount = 0;
	pipe(finalFd);
	pidCount = listLength(command_list);
	printf("%d commands!\n",pidCount );
	while(listLength(command_list) != 0)
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);

		CommandLine* cmd = (CommandLine*)listPopHead(command_list);	
		if(listLength(command_list) == 0)
		{
			lastCommand = 1;
			executeCommand(cmd, lastCommand);
			wait(NULL);
		}
		else
		{
			executeCommand(cmd, lastCommand);
		}
		
//		restoreIO();
		free(cmd);
	}		

	waitAllChildren();

	free(command_list);

}

int doRedirects(CommandLine* cmdLine, int lastCommand)
{
	int success = 0;
	if(cmdLine->inFile != NULL)
	{
		fd_in = open(cmdLine->inFile, O_RDONLY, S_IRUSR | S_IWUSR );
		if(fd_in!=-1)
		{
			dup2(fd_in, STDIN_FILENO); // redirect stdin from file
			success = 1;
		}
	}
	if(cmdLine->outFile != NULL)
	{
		fd_out = open(cmdLine->outFile, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
		if(fd_out!=-1)
		{
			dup2(fd_out, STDOUT_FILENO); // redirect stdout to file
			success = 1;
		}
	}
	else if(lastCommand && cmdLine->outFile == NULL)
	{
		dup2(finalFd[1], STDOUT_FILENO);
		success = 1;
	}
	return success;
}

void executeCommand(CommandLine* cmdLine, int lastCommand)
{
	char** arr = paramListToArray(cmdLine);
	
	if(checkBuiltInParent(cmdLine))
	{
		// do nothing, 
	}
	else
	{
		if(fork() == 0)
		{	/*Child */
			doRedirects(cmdLine, lastCommand);
			if( execvp(cmdLine->command, arr) == -1)
			{
				printf("No such command: %s", arr[0]);
				_exit(1);
			}			
		}
	} 	
}

		
