CC = g++
INC = include
LIB = lib


all: main
Net.o: $(LIB)/Net.cpp
	   $(CC) -c $(LIB)/Net.cpp
Ball.o: $(LIB)/Ball.cpp
		$(CC) -c $(LIB)/Ball.cpp
Paddle.o: $(LIB)/Paddle.cpp
		  $(CC) -c $(LIB)/Paddle.cpp
Score.o: $(LIB)/Score.o
		 $(CC) -c $(LIB)/Score.cpp
main: main.cpp Ball.o Paddle.o Net.o Score.o
		$(CC) -o main main.cpp Ball.o Paddle.o Score.o Net.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
		rm *.o