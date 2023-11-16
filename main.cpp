#include <string>
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "include/Ball.h"
#include "include/Paddle.h"
#include "include/Score.h"
#include "include/Vec2.h"

//first we have to set window height and width
const int WINDOW_HEIGHT = 720;
const int WINDOW_WIDTH  = 1280;

//ball dimensions
const int BALL_WIDTH   = 16;
const int BALL_HEIGHT  = 16;
const float BALL_SPEED = 0.5f;

//paddle dimensions
const int PADDLE_WIDTH    = 10;
const int PADDLE_HEIGHT   = 100;
const float PADDLE_SPEED  = 0.5f;

enum Buttons
{
    Top = 0,
    Bottom,
    Left,
    Right
};

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window   *window    = SDL_CreateWindow("My pong",0,0,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer  = SDL_CreateRenderer(window,-1,0);

    Ball ball(Vec2(WINDOW_WIDTH/2.0f - BALL_WIDTH/2.0f , WINDOW_HEIGHT/2.0f),
              Vec2(0,0),
              BALL_WIDTH, BALL_HEIGHT);

    Paddle paddleOne(Vec2(50.0f, WINDOW_HEIGHT/2.0f - PADDLE_HEIGHT/2.0f),
                     Vec2(0,0),
                     PADDLE_WIDTH, PADDLE_HEIGHT);

    Paddle paddleTwo(Vec2(WINDOW_WIDTH - PADDLE_WIDTH - 50.0f, WINDOW_HEIGHT/2.0f - PADDLE_HEIGHT/2.0f),
                     Vec2(0,0),
                     PADDLE_WIDTH, PADDLE_HEIGHT);

    {//game logic
        bool running = true;
        while(running)
        {
            SDL_Event event;
            while(SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    running = false;
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        running = false;
                    }
                }

            }
            //coloring the window
            SDL_SetRenderDrawColor(renderer, 0x0,0x0,0x0,0xFF);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0xFF);

            for (int y=0; y<WINDOW_HEIGHT; ++y)
            {
                if(y%20 < 10)
                {
                    SDL_RenderDrawPoint(renderer,WINDOW_WIDTH/2.0f, y);
                    SDL_RenderDrawPoint(renderer, WINDOW_WIDTH-50.0f, y);
                    SDL_RenderDrawPoint(renderer, 50.0f, y);
                }
            }
            ball.Draw(renderer);
            paddleOne.Draw(renderer);
            paddleTwo.Draw(renderer);

            SDL_RenderPresent(renderer);
        }
    }

    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}