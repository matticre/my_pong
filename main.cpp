#include <string>
#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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
    PaddleOneUp = 0,
    PaddleOneDown,
    PaddleTwoUp,
    PaddleTwoDown,
};
//Object classes
class Vec2
{   
    public:
        Vec2(): 
            m_x(0x0f), m_y(0.0f){};

        Vec2(float x, float y): m_x(x), m_y(y){};
        float GetX() const {return m_x;};
        float GetY() const{return m_y;};
        void  SetX(const float &x) {m_x = x;};   
        void  SetY(const float &y) {m_y = y;};

        Vec2 operator+(Vec2 const &vec) {return Vec2(m_x + vec.m_x , m_y + vec.m_y);};
        Vec2& operator+=(Vec2 const &vec)
        {
            m_x += vec.m_x;
            m_y += vec.m_y;
            return *this;
        };
        Vec2 operator*(const float &c) { return Vec2(c* m_x, c*m_y);};

        float m_x;
        float m_y;
};

class Ball
{
    public:
        //using Vec2::Vec2;
        Ball(Vec2 position,Vec2 velocity):
            m_position(position), m_velocity(velocity)
        {
            m_rect.x = static_cast<int>(position.GetX());
            m_rect.y = static_cast<int>(position.GetY());
            m_rect.w = BALL_WIDTH;        
            m_rect.h = BALL_HEIGHT;
        };

        void Update(float &dt)
        {
            m_position += m_velocity * dt;
        }

        void Draw(SDL_Renderer *renderer) 
        {
            m_rect.x = static_cast<int>(m_position.GetX());
            m_rect.y = static_cast<int>(m_position.GetY());
            SDL_RenderFillRect(renderer, &m_rect);
        }

        float GetX() const {return m_position.GetX();}
        float GetY() const {return m_position.GetY();}

        void SetVx(float vx)
        {
            m_velocity.SetX(vx);
        }
        
        void SetVy(float vy)
        {
            m_velocity.SetY(vy);
        }

        float GetVx()
        {
            return m_velocity.GetY();
        }
        
        float GetVy()
        {
            return m_velocity.GetY();
        }

        Vec2 m_position;
        Vec2 m_velocity;
        SDL_Rect m_rect;
};

class Paddle
{
    public:
        Paddle(Vec2 position,Vec2 velocity, int width, int height):
            m_position(position), m_velocity(velocity), m_width(width), m_height(height)
        {
            m_rect.x = static_cast<int>(position.GetX());
            m_rect.y = static_cast<int>(position.GetY());
            m_rect.w = PADDLE_WIDTH;
            m_rect.h = PADDLE_HEIGHT;
        };
        
        void Update(float &dt)
        {
            m_position += m_velocity * dt;
            
            if (m_position.GetY() < 0)
            {
                m_position.SetY(0);
            }
            else if (m_position.GetY() > (WINDOW_HEIGHT - PADDLE_HEIGHT))
            {
                m_position.SetY(WINDOW_HEIGHT - PADDLE_HEIGHT);
            }
        };
        
        void Draw(SDL_Renderer *render)
        {
            m_rect.y = static_cast<int>(m_position.GetY());
            SDL_RenderFillRect(render, &m_rect);
        };

        float GetX() const {return m_position.GetX();}
        float GetY() const {return m_position.GetY();}

        void SetVy(float vy)
        {
            m_velocity.SetY(vy);
        }

        Vec2 m_position;
        Vec2 m_velocity;
        int  m_width;
        int  m_height;
        SDL_Rect m_rect;
};

class PlayerScore
{
    public:
        PlayerScore(Vec2 position, SDL_Renderer *renderer, TTF_Font *font): renderer(renderer), font(font)
        {
            surface = TTF_RenderText_Solid(font, "0", {0xFF,0xFF,0xFF,0xFF});
            texture = SDL_CreateTextureFromSurface(renderer, surface);

            int width, height;
            SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

            rect.x = static_cast<int>(position.GetX());
            rect.y = static_cast<int>(position.GetY());
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

        SDL_Renderer *renderer;
        TTF_Font *font;
        SDL_Surface *surface{};
        SDL_Texture *texture{};
        SDL_Rect rect{};
};

bool CheckPaddleCollision(Ball const &ball, Paddle const &paddle)
{
    float ballLeft  = ball.GetX();
    float ballRight = ball.GetX() + BALL_WIDTH;
    float ballTop   = ball.GetY();
    float ballBot   = ball.GetY() + BALL_HEIGHT;

    float paddleLeft  = paddle.GetX();
    float paddleRight = paddle.GetX() + PADDLE_WIDTH;
    float paddleTop   = paddle.GetY();
    float paddleBot   = paddle.GetY() + PADDLE_HEIGHT;

    if(ballLeft >= paddleRight)
    {
        return false;
    }
    else if (ballRight <= paddleLeft)
    {
        return false;
    }
    else if (ballTop >= paddleBot)
    {
        return false;
    }
    else if (ballBot <= paddleTop)
    {
        return false;
    }

    return true;
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window   *window    = SDL_CreateWindow("My pong",0,0,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer  = SDL_CreateRenderer(window,-1,0);

    //Initializing fonts and player score
    TTF_Font     *scorefont = TTF_OpenFont("DejaVuSansMono.ttf", 40);

    PlayerScore playerOneScoreText(Vec2(WINDOW_WIDTH / 4, 20), renderer, scorefont);
    PlayerScore playerTwoScoreText(Vec2(3 * WINDOW_WIDTH / 4, 20), renderer, scorefont);


    Ball ball(Vec2(WINDOW_WIDTH/2.0f - BALL_WIDTH/2.0f , WINDOW_HEIGHT/2.0f),
              Vec2(BALL_SPEED,0));

    Paddle paddleOne(Vec2(50.0f, WINDOW_HEIGHT/2.0f - PADDLE_HEIGHT/2.0f),
                     Vec2(0,0),
                     PADDLE_WIDTH, PADDLE_HEIGHT);

    Paddle paddleTwo(Vec2(WINDOW_WIDTH - PADDLE_WIDTH - 50.0f, WINDOW_HEIGHT/2.0f - PADDLE_HEIGHT/2.0f),
                     Vec2(0,0),
                     PADDLE_WIDTH, PADDLE_HEIGHT);

    {   //game logic
        bool running    = true;
        bool buttons[4] = {};

        float dt = 0.0f;

        while(running)
        {
            auto startTime = std::chrono::high_resolution_clock::now();
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

                if (buttons[Buttons::PaddleOneUp])
                {
                    paddleOne.SetVy(-PADDLE_SPEED);
                }
                else if (buttons[Buttons::PaddleOneDown])
                {
                    paddleOne.SetVy(PADDLE_SPEED);
                }
                else 
                {
                    paddleOne.SetVy(0.0f);
                }
                
                if (buttons[Buttons::PaddleTwoUp])
                {
                    paddleTwo.SetVy(-PADDLE_SPEED);
                }
                else if (buttons[Buttons::PaddleTwoDown])
                {
                    paddleTwo.SetVy(PADDLE_SPEED);
                }
                else 
                {
                    paddleTwo.SetVy(0.0f);
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

            playerOneScoreText.Draw();
            playerTwoScoreText.Draw();

            SDL_RenderPresent(renderer);

            auto stopTime = std::chrono::high_resolution_clock::now();
            dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();

            paddleOne.Update(dt);
            paddleTwo.Update(dt);
            ball.Update(dt);

            //checking collisions
            if (CheckPaddleCollision(ball, paddleOne) || CheckPaddleCollision(ball, paddleTwo))
            {   
                ball.m_velocity.m_x = - ball.m_velocity.m_x;
            }
        }
    }

    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(scorefont);
    TTF_Quit();
    SDL_Quit();

    return 0;
}