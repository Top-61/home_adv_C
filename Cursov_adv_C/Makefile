all: prog
prog: main.o func.o
	gcc main.o func.o -o prog
main.o: main.c
	gcc -c main.c
temp_functions.o: func.c
	gcc -c func.c
clean:
	del main.o func.o prog.exe