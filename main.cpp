#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

//list of possible moves
enum Buttons
{
    PaddleOneUp   = 0,
    PaddleOneDown ,
    PaddleTwoUp   ,
    PaddleTwoDown ,
};

//paddle speed
const float PADDLE_SPEED = 10.0f;
const float BALL_SPEED   = 10.0f;

//first we have to set window height and width
const int WINDOW_HEIGHT = 720;
const int WINDOW_WIDTH  = 1280;

//ball dimensions
const int BALL_WIDTH  = 15;
const int BALL_HEIGHT = 15;

//paddle dimensions
const int PADDLE_WIDTH    = 10;
const int PADDLE_HEIGHT   = 100;

// vettore
class Vec2
{
    public:
        float x,y;

        Vec2(): 
            x(0x0f), y(0x0f)
        {};
        
        Vec2(float x, float y)
            : x(x), y(y)
        {};

        Vec2 operator+(Vec2 const& rhs)
        {
            return Vec2(x + rhs.x, y + rhs.y);
        };

        Vec2& operator+=(Vec2 const& rhs)
        {
            x += rhs.x;
            y += rhs.y;

            return *this;
        };

        Vec2 operator*(float rhs){
            return Vec2(x*rhs, y*rhs);
        };
};

class Ball
{
    public:
        Ball(Vec2 position, Vec2 velocity):
            position(position), velocity(velocity)
        {
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);
            rect.w = BALL_WIDTH;
            rect.h = BALL_HEIGHT;
        }

        void Update(float dt)
        {
            position += velocity * dt;
        }

        void Draw(SDL_Renderer* renderer)
        {
            rect.x = static_cast<int> (position.x);
            rect.y = static_cast<int> (position.y);

            SDL_RenderFillRect(renderer, &rect);        
        }

        Vec2 position;
        Vec2 velocity;
        SDL_Rect rect{};
};

class Paddle
{
    public:
        Paddle(Vec2 position, Vec2 velocity)
            : position(position), velocity(velocity)
        {
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);
            rect.h = PADDLE_HEIGHT;        
            rect.w = PADDLE_WIDTH;
        }

        void Update(float dt)
        {
            position += velocity*dt;

            if (position.y<0)
            {
                position.y = 0;
            } 
            else if (position.y > (WINDOW_HEIGHT - PADDLE_HEIGHT))
            {
                position.y = WINDOW_HEIGHT - PADDLE_HEIGHT;
            }
        }

        void Draw(SDL_Renderer* renderer)
        {
            rect.y = static_cast<int>(position.y);

            SDL_RenderFillRect(renderer, &rect);
        }

        Vec2 position;
        Vec2 velocity;
        SDL_Rect rect{};

};


class PlayerScore
{
    public:
        PlayerScore(Vec2 position, SDL_Renderer* renderer, TTF_Font* font)
            :renderer(renderer), font(font)
        {   
            surface = TTF_RenderText_Solid(font,"0",{0xFF,0xFF,0xFF,0xFF});
            texture = SDL_CreateTextureFromSurface(renderer, surface);

            int width, height;
            SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);
            rect.w = width;                
            rect.h = height;
        }

        ~PlayerScore()
        {
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        void Draw()
        {
            SDL_RenderCopy(renderer, texture, nullptr, &rect);
        }

        SDL_Renderer* renderer;
        TTF_Font* font;
        SDL_Surface* surface{};
        SDL_Texture* texture{};
        SDL_Rect rect{};
};


int main(){
    //second, we have to initialize the layer components
    SDL_Init(SDL_INIT_VIDEO);
    
    //initializing text
    TTF_Init();    

    SDL_Window*   window   = SDL_CreateWindow("Pong",0,0,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);

    //initializing the font
    TTF_Font* scoreFont = TTF_OpenFont("DejaVuSansMono.ttf",40);

    //creating the paddles
    Paddle paddleOne(Vec2(50.0f, (WINDOW_HEIGHT/2.0f - PADDLE_HEIGHT/2.0f)),
                     Vec2(0.0f,0.0f));
    Paddle paddleTwo(Vec2(WINDOW_WIDTH- 50.0f, WINDOW_HEIGHT/2.0f - PADDLE_HEIGHT/2.0f),
                     Vec2(0.0f,0.0f));

    //player text scores
    PlayerScore playerOneScoreText(Vec2(WINDOW_WIDTH/4,20),  renderer, scoreFont);
    PlayerScore playerTwoScoreText(Vec2(3*WINDOW_WIDTH/4,20),renderer, scoreFont);

    //creating the ball
    Ball ball(Vec2((WINDOW_WIDTH/2.0f) - (BALL_WIDTH/2.0f),
                   (WINDOW_HEIGHT/2.0f) - (BALL_HEIGHT/2.0f)),
              Vec2(BALL_SPEED,0.0f));

    //game logic
    {
        bool running    = true;
        bool buttons[4] = {};
        float dt = 0.0f;

        while(running)
        {
            SDL_Event event;
            auto startTime = chrono::high_resolution_clock::now();
            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT)
                {
                    running = false;
                }
                else if(event.type == SDL_KEYDOWN)
                {
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        running = false;
                    }
                    else if(event.key.keysym.sym == SDLK_w)
                    {
                        buttons[Buttons::PaddleOneUp] = true;
                    }
                    else if(event.key.keysym.sym == SDLK_s)
                    {
                        buttons[Buttons::PaddleOneDown] = true;                        
                    }
                    else if(event.key.keysym.sym == SDLK_UP)
                    {
                        buttons[Buttons::PaddleTwoUp] = true;
                    }
                    else if(event.key.keysym.sym == SDLK_DOWN)
                    {
                        buttons[Buttons::PaddleTwoDown] = true;
                    }
                }

                else if(event.type == SDL_KEYUP)
                {
                    if(event.key.keysym.sym == SDLK_w)
                    {
                        buttons[Buttons::PaddleOneUp] = false;
                    }
                    else if(event.key.keysym.sym == SDLK_s)
                    {
                        buttons[Buttons::PaddleOneDown] = false;                        
                    }
                    else if(event.key.keysym.sym == SDLK_UP)
                    {
                        buttons[Buttons::PaddleTwoUp] = false;
                    }
                    else if(event.key.keysym.sym == SDLK_DOWN)
                    {
                        buttons[Buttons::PaddleTwoDown] = false;
                    }
                }

                if(buttons[Buttons::PaddleOneUp])
                {
                    paddleOne.velocity.y = -PADDLE_SPEED;
                }
                else if(buttons[Buttons::PaddleOneDown])
                {
                    paddleOne.velocity.y = PADDLE_SPEED;
                }
                else
                {
                    paddleOne.velocity.y = 0.0f;
                }
                
                if(buttons[Buttons::PaddleTwoUp])
                {
                    paddleTwo.velocity.y = -PADDLE_SPEED;
                }
                else if(buttons[Buttons::PaddleTwoDown])
                {
                    paddleTwo.velocity.y = PADDLE_SPEED;
                }
                else
                {
                    paddleTwo.velocity.y = 0.0f;
                }

                paddleOne.Update(dt);
            	paddleTwo.Update(dt);
                ball.Update(dt);
            }
        //coloring the window
        SDL_SetRenderDrawColor(renderer, 0x0,0x0,0x0,0xFF);
        SDL_RenderClear(renderer);
        
        //setting the color for the net
        SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
        //drawing the net
        for (int y=0; y<WINDOW_HEIGHT; ++y)
        {
            if (y%5)
            {
                SDL_RenderDrawPoint(renderer, WINDOW_WIDTH/2, y);
            }
        }

        //drawing the ball
        ball.Draw(renderer);

        //drawing paddle
        paddleOne.Draw(renderer);
        paddleTwo.Draw(renderer);

        //drawing the scores
        playerOneScoreText.Draw();
        playerTwoScoreText.Draw();
        //backbuffer
        SDL_RenderPresent(renderer);

        auto stopTime = chrono::high_resolution_clock::now();
        dt = chrono::duration<float, chrono::milliseconds::period>(stopTime-startTime).count();
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(scoreFont);
    TTF_Quit();
    SDL_Quit();

    return 0;
} 