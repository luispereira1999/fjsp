all: main

main: main.o menu.o stage1.o
	gcc -g -o main main.o menu.o stage1.o

main.o: main.c stage1.h
	gcc -g -o main.o main.c -c

menu.o: menu.c stage1.h
	gcc -g -o menu.o menu.c -c

stage1.o: stage1.c stage1.h
	gcc -g -o stage1.o stage1.c -c

clean:
	del /Q /S *.o *~ main

run:
	mingw32-make clean
	mingw32-make all
	./main