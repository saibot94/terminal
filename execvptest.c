#include <stdio.h>
#include <unistd.h>
int main()
{
	char* params[] = {"nl","term.c","-s=hola",NULL};
	pid_t pid = fork();
	if(pid == 0){
		execvp("nl",params);
	}
	else{
		wait(pid);
	}
	return 0;
}
