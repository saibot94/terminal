all: milestone_3

milestone_3: cd.o term_exec.o term_signals.o term_parser.o term_history.o term_utils.o term_texted.o term.o list.o
	gcc -o milestone_3 term_exec.o term_signals.o cd.o term_parser.o term_history.o term_utils.o term_texted.o term.o list.o -lhistory

term.o: term.c
	gcc -c term.c

cd.o: cd.c
	gcc -c cd.c

term_signals.o: term_signals.c
	gcc -c term_signals.c

term_parser.o: term_parser.c
	gcc -c term_parser.c

term_history.o: term_history.c
	gcc -c term_history.c

term_utils.o: term_utils.c
	gcc -c term_utils.c

term_texted.o: term_texted.c
	gcc -c term_texted.c

list.o: list.c
	gcc -c list.c

term_exec.o: term_exec.c
	gcc -c term_exec.c

clean:
	rm -rf *o milestone_3
