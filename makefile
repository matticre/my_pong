CC = g++
INC = include/
LIB = lib/
SDL2 = -lSDL2
SDL2TTF = -lSDL2_ttf
SDL2MIX = -lSDL2_mixer


all: main
Vec2.o: $(LIB)Vec2.cpp
	$(CC) -c $(LIB)Vec2.cpp
main: main.cpp Vec2.o
	$(CC) -o main main.cpp Vec2.o $(SDL2) $(SDL2TTF) $(SDL2MIX)
	rm -rf *.o