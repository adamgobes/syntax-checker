syntax_checker : main.o parse.o syntax.o
	gcc -o syntax_checker main.o parse.o syntax.o

main.o : main.c parse.h syntax.h
	gcc -c main.c

parse.o : parse.c parse.h
	gcc -c parse.c

syntax.o : syntax.c syntax.h
	gcc -c syntax.c

clean :
	rm syntax_checker
