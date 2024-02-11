CC = g++
INC = include
LIB = lib


all: main
Ball.o: $(LIB)/Ball.cpp
		$(CC) -c $(LIB)/Ball.cpp
main: main.cpp Ball.o
		$(CC) -o main main.cpp Ball.o -lsfml-graphics -lsfml-window -lsfml-system
		rm *.o