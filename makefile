CC = g++
SDL2 = -lSDL2
SDL2TTF = -lSDL2_ttf
SDL2MIX = -lSDL2_mixer

all: my_pong

my_pong: main.cpp 
	$(CC) -o my_pong main.cpp $(SDL2) $(SDL2TTF) $(SDL2MIX)
clean:
	rm *.o
