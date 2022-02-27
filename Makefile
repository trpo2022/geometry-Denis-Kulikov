all: ex
	
ex: main.c
	gcc -Wall -Werror -o ex main.c
clear:
	rm ex
run:
	./ex
