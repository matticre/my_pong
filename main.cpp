#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

enum Buttons
{
    PaddleOneUp   = 0,
    PaddleOneDown = 0,
    PaddleTwoUp   = 0,
    PaddleTwoDown = 0,
};

const int WINDOW_WIDTH  = 1280;
const int WINDOW_HEIGHT = 720;
const int BALL_WIDTH    = 15;
const int BALL_HEIGHT   = 15;
const int PADDLE_WIDTH    = 10;
const int PADDLE_HEIGHT   = 100;

const float PADDLE_SPEED  = 1.0f;

class Vec2
{
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

        float x,y;
};

class Ball
{   
    
    public:
        Ball(Vec2 position) : position(position)
        {
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);
            rect.h = BALL_HEIGHT;
            rect.w = BALL_WIDTH;
        }

        void Draw(SDL_Renderer* renderer )
        {
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);

            SDL_RenderFillRect(renderer, &rect); 
        } 

        Vec2 position;
        SDL_Rect rect{};


};

class Paddle
{
    public:
        Paddle(Vec2 position, Vec2 velocity) : position(position), velocity(velocity)
        {
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);
            rect.h = PADDLE_HEIGHT;
            rect.w = PADDLE_WIDTH;
        }

        void Update (float dt)
        {
            position += velocity * dt;

            if (position.y<0)
            {
                position.y=0;
            }
            else if (position.y > (WINDOW_HEIGHT - PADDLE_HEIGHT) )
            {
                position.y = WINDOW_HEIGHT - PADDLE_HEIGHT;
            }
        }


        void Draw(SDL_Renderer* renderer )
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

        SDL_Renderer* renderer;
        TTF_Font* font;
        SDL_Surface* surface{};
        SDL_Texture* texture{};
        SDL_Rect rect{};

        PlayerScore(Vec2 position, SDL_Renderer* renderer, TTF_Font* font) : renderer(renderer), font(font)
        {
            surface = TTF_RenderText_Solid(font, "0", {0xFF, 0xFF, 0xFF, 0xFF});
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

};



int main (){

    // Initialization 
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Pong",0,0,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);

    // Font initialization
    TTF_Font* scoreFont = TTF_OpenFont("DejaVuSansMono.ttf",40);

    // Creation of the score text
    PlayerScore playerOneScoreText( Vec2(    WINDOW_WIDTH / 4, 20 ), renderer, scoreFont);
    PlayerScore playerTwoScoreText( Vec2(3 * WINDOW_WIDTH / 4, 20 ), renderer, scoreFont);

    // creating the ball
    Ball ball (Vec2( (WINDOW_WIDTH / 2.0f) - (BALL_WIDTH/2.0f), (WINDOW_HEIGHT / 2.0f) - (BALL_HEIGHT/2.0f) ));
    
    // creating the paddles
    Paddle paddleOne( Vec2( 50.0f, WINDOW_HEIGHT/2.0f - PADDLE_HEIGHT/2.0f), Vec2(0.0f,0.0f));
    Paddle paddleTwo( Vec2( WINDOW_WIDTH - 50.0f, WINDOW_HEIGHT/2.0f - PADDLE_HEIGHT/2.0f), Vec2(0.0f,0.0f));

    // Game logic
    {
        bool running = true;
        bool buttons[4] = {};

        float dt = 0.0f;

        // This keeps the program running 
        while (running)
        {
            auto startTime = std::chrono::high_resolution_clock::now();
            SDL_Event event;
            while (SDL_PollEvent(&event)){

                if (event.type == SDL_QUIT){
                    running = false;
                }

                else if (event.type == SDL_KEYDOWN){
                   
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        running = false;
                    }
                    else if (event.key.keysym.sym == SDLK_w)
                    {
                        buttons[Buttons::PaddleOneUp] = true;
                    }
                    else if (event.key.keysym.sym == SDLK_s)
                    {
                        buttons[Buttons::PaddleOneDown] = true;                    
                    }
                    else if (event.key.keysym.sym == SDLK_UP)
                    {
                        buttons[Buttons::PaddleTwoUp] = true;
                    }
                    else if (event.key.keysym.sym == SDLK_DOWN)
                    {
                        buttons[Buttons::PaddleTwoDown] = true;
                    
                    }
                } 

                else if (event.type == SDL_KEYUP)

                {
                    if (event.key.keysym.sym == SDLK_w)
                    {
                        buttons[Buttons::PaddleOneUp] = false;
                    }
                    else if (event.key.keysym.sym == SDLK_s)
                    {
                        buttons[Buttons::PaddleOneDown] = false;
                    }
                    else if (event.key.keysym.sym == SDLK_UP)
                    {
                        buttons[Buttons::PaddleTwoUp] = false;
                    }
                    else if (event.key.keysym.sym == SDLK_DOWN)
                    {
                        buttons[Buttons::PaddleTwoDown] = false;
                    }
                }
            }

            //associating velocity - paddle one
            if (buttons[Buttons::PaddleOneUp])
            {
                paddleOne.velocity.y = - PADDLE_SPEED;
            }    
            else if (buttons[Buttons::PaddleOneDown])
            {
                paddleOne.velocity.y = PADDLE_SPEED;
            }
            else
            {
                paddleOne.velocity.y = 0.0f;
            }

            // associating velocity - paddle two
            if (buttons[Buttons::PaddleTwoUp])
            {
                paddleTwo.velocity.y = - PADDLE_SPEED;
                std :: cout << "prova" << "\n";

            }    
            else if (buttons[Buttons::PaddleTwoDown])
            {
                paddleTwo.velocity.y = PADDLE_SPEED;
            }
            else
            {
                paddleTwo.velocity.y = 0.0f;
            }

            paddleOne.Update(dt);
            paddleTwo.Update(dt);

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

            // Disblaying ball and paddles
            ball.Draw(renderer);
            paddleOne.Draw(renderer);
            paddleTwo.Draw(renderer);

            // Displaying the score            
            playerOneScoreText.Draw();
            playerTwoScoreText.Draw();

            // Backbuffer 
            SDL_RenderPresent(renderer);
       
            // Calculating time frame
            auto stopTime = std::chrono::high_resolution_clock::now();
            dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime-startTime).count();
        }

    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(scoreFont);
    TTF_Quit();
    SDL_Quit();

    return 0;
}