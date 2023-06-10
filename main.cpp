#include <iostream>
#include <SDL2/SDL.h>

const int WINDOW_WIDTH  = 1280;
const int WINDOW_HEIGHT = 720;
const int BALL_WIDTH    = 15;
const int BALL_HEIFHT   = 15;


class Vec2
{
    private:
        float x,y;

    public:
        Vec2(): 
            x(0.0f), y(0.0f)
        {}
        
        Vec2(float x, float y):
            x(x), y(y)
        {}

        Vec2 operator+(const Vec2& rhs)
        {
            return Vec2(x+rhs.x,y+rhs.y);
        }

        Vec2& operator+=(const Vec2& rhs)
        {
            x += rhs.x;
            y += rhs.x;
        
            return *this;
        }

        Vec2 operator*(float rhs)
        {
            return Vec2(x*rhs ,y*rhs);
        }

};

class Ball{

};



int main (){

    // Initialization 
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Pong",0,0,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);

    // Game logic
    {
        bool running = true;

        // This keeps the program running 

        while (running)
        {

            SDL_Event event;
            while (SDL_PollEvent(&event)){

                if (event.type == SDL_QUIT){
                    running = false;
                }

                else if (event.type == SDL_KEYDOWN){
                   
                    if (event.key.keysym.sym == SDLK_ESCAPE){
                        running = false;
                    }
                
                } 

            }
            

            // Black window
            SDL_SetRenderDrawColor(renderer, 0x0,0x0,0x0,0xFF);
            SDL_RenderClear(renderer);

            // White net
            SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF ); // Setting draw color to be white

            // Actually drawing
            int n_dots = 5;
            for (int y=0; y < WINDOW_HEIGHT; ++y )
            {

                if (y % 5)
                {            
                    SDL_RenderDrawPoint(renderer, WINDOW_WIDTH/2, y);
                }
            } 

            // Backbuffer 
            SDL_RenderPresent(renderer);
       
        }

    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}