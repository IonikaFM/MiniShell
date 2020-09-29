build: file.h main.h list.h file.c list.c main.c
	gcc -o minishell file.c list.c main.c
run:
	./minishell
