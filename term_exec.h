#ifndef TERM_EXEC_H
#define TERM_EXEC_H 
#include "stdafx.h"
#include <unistd.h>
#include <errno.h>
#include "list.h"
#include "term_cmd_line.h"
#include "term_commands.h"
#include "term_utils.h"
#include <fcntl.h>

void executeCommandList(List* command_list);

#endif