#include "term_texted.h"

/*extern char buffer[BUFFER_SIZE * BUFFER_SIZE]; 
extern int cursorPos;					// Current position of the cursor 
extern int currentLinePos ;				// Current position of the line-end
extern int historyPos;					// Current position in the history
*/


char prevKey = 0;


/* Shifts the command line characters from the 
	current position to the right one character */
void shiftBufferPosRight()
{
	int i;
	for(i = currentLinePos; i > cursorPos; i--)
	{
		buffer[i] = buffer[i-1];
	}
}
/* Shifts the command line characters from the 
	current position to the left one character */
void shiftBufferPosLeft()
{
	int i;
	for(i = cursorPos; i <currentLinePos; i++)
	{
		buffer[i] = buffer[i+1];
	}
}

/* Redraws current line on screen */
void redrawLine()
{
	int i;
	for(i = 0; i <= currentLinePos + CMD_PROMPT_SIZE; i++)
	{
		REMOVE_CHAR	
	}
	printf(CMD_PROMPT_NO_NEWLINE);
	for(i = 0; i < currentLinePos; i++)
	{
	putchar(buffer[i]);
	}
	for(i = 0; i < currentLinePos - cursorPos; i++)
	{
		printf("\033[D");		
	}
	fflush(stdout);
}

/* Removes everything on the current line */
void deleteLine()
{
	int i;
	for(i = 0; i <= currentLinePos + CMD_PROMPT_SIZE; i++)
	{
		REMOVE_CHAR	
	}
	fflush(stdout);
}


void handleCharacter(char c)
{
	int j = 1, i;
	if(c != '\t')
	{	
		if(cursorPos < currentLinePos)
		{
			currentLinePos++;
			shiftBufferPosRight();
			buffer[cursorPos++] = c;		
		}
		else
		{
			currentLinePos++;
			buffer[cursorPos++] = c;
			putchar(c);
		}
	}

}

void handleBackspace()
{
	if(cursorPos > 0)
	{
		buffer[currentLinePos] ='\0';
		cursorPos--;
		currentLinePos--;
		if(cursorPos < currentLinePos)
		{	
			shiftBufferPosLeft();				
		}
		else
		{
			REMOVE_CHAR
		}
	}
}

void handleRightKey()
{
	if(cursorPos < currentLinePos)
	{
		cursorPos++;
		printf("\033[C"); // Moves cursor to the right
	}
}

void handleLeftKey()
{
	if(cursorPos > 0)
	{
		cursorPos--;
		printf("\033[D"); // Moves cursor to the left
	}
}

void handleUpKey()		
{
	HISTORY_STATE* state = history_get_history_state();
	int i;
	empty_buffer();
	deleteLine();
	if(historyPos > history_length)
	{
		historyPos = history_length;
	}
	else if(prevKey == DOWN_KEY)
	{
		historyPos-=2;
	}
	if(historyPos > 0)
	{
		HIST_ENTRY* last_entry = history_get(historyPos--);
		if(last_entry) /* if we haven't reached the end of the history */ 
		{
			for(i = 0; last_entry->line[i];i++)
			{
				buffer[i] = last_entry->line[i]; 
			}
			currentLinePos = i;
			cursorPos=currentLinePos;
			redrawLine();	
			//buffer[i];
		}
	}
	else
	{
		deleteLine();
		currentLinePos=0;
		redrawLine();
		cursorPos=0;
	}
	
}

void handleDownKey()
{
	HISTORY_STATE* state = history_get_history_state();
	int i;
	empty_buffer();
	deleteLine();
	if(historyPos == 0)
	{
		historyPos++;
	}
	else if(prevKey == UP_KEY)
	{
		historyPos+=2;
	}
	if(historyPos < history_length + 1)
	{
		HIST_ENTRY* last_entry = history_get(historyPos++);
		if(last_entry) /* if we haven't reached the end of the history */ 
		{

			for(i = 0; last_entry->line[i];i++)
			{
				buffer[i] = last_entry->line[i]; 
			}
			currentLinePos = i;
			cursorPos=currentLinePos;
			redrawLine();
		}
	}
	else
	{
		historyPos = history_length + 1;
		empty_buffer();
		currentLinePos =0;
		cursorPos = 0;
		deleteLine();
	}
}

int isEmpty(char* buffer)
{
	int i;
	char* trimmed = trim(buffer);
	for(i =0 ;i<strlen(trimmed);i++)
	{
		if(trimmed[i] != ' ')
		{
			return 0;
		}
	}
	return 1;
}

void processLine()
{
	extendHistory(trim(buffer));
	List* command_list = parse_command(buffer, currentLinePos);
	executeCommandList(command_list);
}




void parse_char(char c)
{
	if(c == 10) /* Enter was pressed */
	{
		if(currentLinePos!=0)
		{
			if(!isEmpty(buffer))
			{
				processLine();				
			}
		}
		empty_buffer();
		cursorPos=0;			
		currentLinePos = 0;
		resetHistoryPos();
		printf(CMD_PROMPT);				
		
	}
	else if(c == ESCAPE_KEY) /* Escape character found */ 
	{

		system("stty raw ");
		c = getchar();
		c = getchar();
		system("stty cooked -icanon");
		if(c == UP_KEY)
		{
			handleUpKey();
			prevKey = UP_KEY;
		}
		if(c == DOWN_KEY)
		{
			handleDownKey();
			prevKey = DOWN_KEY;
		}
		if(c == LEFT_KEY)
		{
			handleLeftKey();
		}
		if(c == RIGHT_KEY)
		{
			handleRightKey();
		}
	}
	else if(c == BACKSPACE) /* Backspace pressed */
	{
		handleBackspace();
	}
	else
	{
		handleCharacter(c);
	}	
	prevKey = c;
	redrawLine();
}