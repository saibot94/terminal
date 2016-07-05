#ifndef TERM_HISTORY_H
#define TERM_HISTORY_H 

#include "stdafx.h"
#include "readline/history.h"
/* Init history */
void init_history();

/* Resets history to the last entry */
void resetHistoryPos();

/* Adds 'char* buffer' to the history */ 
void extendHistory(char* buffer);

#endif
