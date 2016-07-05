#include "term_history.h"

extern int historyPos;		

void init_history()
{
	historyPos = 0;
	using_history();
}

void resetHistoryPos()
{
	historyPos = history_length;
}

void extendHistory(char* buffer)
{	
	HISTORY_STATE* state = history_get_history_state();
	buffer[currentLinePos] = '\0';
	add_history(buffer);
	resetHistoryPos();
}

