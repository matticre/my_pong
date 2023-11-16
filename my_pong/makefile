BCC = g++
SDL2 = -lSDL2
SDL2TTF = -lSDL2_ttf

all: my_pong

Ball.o : Ball.cpp Ball.h
	$(CC) -c Ball.o include/Ball.cpp $(SDL2) $(SDL2TTF)

my_pong: main.cpp include/Ball.cpp 
	$(CC) -o my_pong main.cpp $(SDL2) $(SDL2TTF)
clean:
	rm *.o
