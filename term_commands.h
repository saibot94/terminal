#ifndef TERM_COM_H
#define TERM_COM_H
#include <errno.h>

/* Declarations of the functions that need to be implemented into the terminal */
int cd(int argc, char** argv);
int mv(int argc, char** argv);
int nl(int argc, char** argv);

#endif // TERM_COM_H 