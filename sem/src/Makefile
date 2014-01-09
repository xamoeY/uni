cc = gcc
flags =  -O0 -Wall -Wshadow -Wextra -Wpacked -Wpadded -pedantic -std=gnu99
default: compile run

compile:
	${cc} ${flags} -o example1 example1.c
	${cc} ${flags} -o example2 example2.c
	${cc} ${flags} -o example3 example3.c
	${cc} ${flags} -o example4 example4.c
	${cc} ${flags} -o example5 example5.c
	${cc} ${flags} -o example6 example6.c
	${cc} ${flags} -std=c11 -o example7 example7.c
	${cc} ${flags} -S -fno-asynchronous-unwind-tables -o example8.s example8.c

run:
	./example1
	./example2
	./example3
	./example4
	./example5
	./example6
	./example7
