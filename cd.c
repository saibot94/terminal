#include "term_commands.h"
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>


int cd(int argc, char** argv)
{

	if(argc < 2)
	{
		printf(" Error: cd must be passed a valid path! \n");
		return 1;
	}
	else
	{
		if(chdir(argv[1])) {
			perror("Error ");
		}
	}

	return 0;
}