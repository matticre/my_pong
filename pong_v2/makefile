CC = g++
SDL2 = -lSDL2
SDL2TTF = -lSDL2_ttf

all: out

Ball.o : Ball.cpp Ball.h
	$(CC) -c Ball.o include/Ball.cpp $(SDL2) $(SDL2TTF)

out: main.cpp include/Ball.cpp 
	$(CC) -o out main.cpp $(SDL2) $(SDL2TTF)
clean:
	rm *.o
