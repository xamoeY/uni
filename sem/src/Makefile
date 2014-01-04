flags =  -O0 -Wall -Wshadow -Wextra -Wpacked -Wpadded -pedantic -std=gnu99
default: compile run

compile:
	gcc ${flags} -o example1 example1.c
	gcc ${flags} -o example2 example2.c
	gcc ${flags} -o example3 example3.c
	gcc ${flags} -o example4 example4.c
	gcc ${flags} -S example5.c

run:
	./example1
	./example2
	./example3
	./example4
