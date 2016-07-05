
#include <stdio.h>
#include "list.h"
#include "term_cmd_line.h"
#include <string.h>

static char* trim(char* toTrim)
{
	int i,j, cnt = 0;
	char* newString = (char*) malloc(sizeof(char) * strlen(toTrim));
	if(strlen(toTrim) > 2)
	{
		for(i = 0; (toTrim[i] == ' ' || toTrim[i] == '\n')  && i < strlen(toTrim); i++)
		{
			// loop while there's a space at the start
		}
		for(j = strlen(toTrim) - 2; (toTrim[j] == ' ' || toTrim[j] == '\n') && j >=0 ; j--)
		{
			// loop while there's a space at the end
		}
		if(i < j)
		{
			for( ; i <=j; i++)
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


int main(int argc, char const *argv[])
{
	while(1)
	{
	char buf[256];
	fgets(buf, 255, stdin);
	buf[strlen(buf)] = '\0';
	char* newBuf = trim(buf);
	strcat(newBuf,"...check");
	printf("Trimmed %d",newBuf[strlen(newBuf)-1] == '\n');
	printf("strlen = %d\n",strlen(newBuf) );
	}
	return 0;
};