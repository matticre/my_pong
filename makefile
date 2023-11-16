BCC = g++
SDL2 = -lSDL2
SDL2TTF = -lSDL2_ttf

all: my_pong

Vec2.o : Vec2.cpp Vec2.h
	$(CC) -c Vec2.o include/Vec2.cpp $(SDL2) $(SDL2TTF)

Ball.o : Ball.cpp Ball.h
	$(CC) -c Ball.o include/Ball.cpp $(SDL2) $(SDL2TTF)

my_pong: main.cpp include/Ball.cpp 
	$(CC) -o my_pong main.cpp $(SDL2) $(SDL2TTF)
clean:
	rm *.o
