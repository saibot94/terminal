#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include "readline/history.h"
#include <stdlib.h>
#include <unistd.h>

#include "term_defines.h"
#include "term_vars.h"
#include "term_commands.h"
#include "term_utils.h"


int main(int argc, char const *argv[])
{
	using_history();
	unsigned char c,pressed_key;
	signal(SIGINT, reset_term);
	system("stty -icanon -echo");
	
	printf(CMD_PROMPT);
	while(c = getc(stdin)) /* Main input loop */ 
	{
		parse_char(c);
		redrawLine();
	}
	system("stty cooked canon echo");
	return 0;
}
