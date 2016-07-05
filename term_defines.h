#ifndef TERM_CONFIG_H
#define TERM_CONFIG_H

/* \:\:\: */

#define UP_KEY 65
#define DOWN_KEY 66
#define LEFT_KEY 68
#define RIGHT_KEY 67
#define ENTER_KEY 10
#define BACKSPACE 127
#define ESCAPE_KEY 27

#define CMD_PROMPT "\n$> " 
#define CMD_PROMPT_NO_NEWLINE "$> "
#define CMD_PROMPT_SIZE 2
#define BUFFER_SIZE 512
#define ARGSIZE 128

#define REMOVE_CHAR printf("\b\033[K");



#endif
