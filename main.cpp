#include "include/Vec2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>
#include <chrono>


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
    PaddleOneUp,
    PaddleOneDown,
    PaddleTwoUp,
    PaddleTwoDown,
};

enum class CollisionType
{
    None,
    Top,
    Middle,
    Bottom,
    Left,
    Right,
};

struct Contact
{
    CollisionType type;
    float penetration;
};

//object classes
/* class Vec2
{   
    public:
        Vec2(): 
            m_x(0x0f), m_y(0.0f){};

        Vec2(float x, float y): m_x(x), m_y(y){};
        float GetX() const {return m_x;};
        float GetY() const {return m_y;};
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
    
    private:
        float m_x;
        float m_y;
}; */

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

        void CollideWithPaddle(Contact const& contact)
        {
            m_position.SetX( m_position.GetX() + contact.penetration);
            m_velocity.SetX( - m_velocity.GetX());

        
            if (contact.type == CollisionType::Top)
            {
                m_velocity.SetY( - 0.75 * BALL_SPEED);
            }
            else if (contact.type == CollisionType::Bottom)
            {
                m_velocity.SetY( 0.75 * BALL_SPEED);
            }
        }

        void CollideWithWall (Contact const& contact)
        {
            if ((contact.type == CollisionType::Top) || (contact.type == CollisionType::Bottom))
            {
                m_position.SetY( m_position.GetY() + contact.penetration);
                m_velocity.SetY( - m_velocity.GetY());
            }
            else if (contact.type == CollisionType::Left)
            {
                m_position.SetX( WINDOW_WIDTH / 2.0f );
                m_position.SetY( WINDOW_HEIGHT / 2.0f );
                m_velocity.SetX( -BALL_SPEED );
                m_velocity.SetY( 0.0f );
            }
            else if (contact.type == CollisionType::Right)
            {    
                m_position.SetX( WINDOW_WIDTH / 2.0f );
                m_position.SetY( WINDOW_HEIGHT / 2.0f );
                m_velocity.SetX( BALL_SPEED );
                m_velocity.SetY( 0.0f );
            }
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

        void SetScore(int score)
        {
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);

            surface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), {0xFF,0xFF,0xFF,0xFF});
            texture = SDL_CreateTextureFromSurface(renderer, surface);

            int width, height;
            SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
            rect.w = width;
            rect.h = height;
        }

        SDL_Renderer *renderer;
        TTF_Font *font;
        SDL_Surface *surface{};
        SDL_Texture *texture{};
        SDL_Rect rect{};
};

Contact CheckPaddleCollision(Ball const &ball, Paddle const &paddle)
{
    float ballLeft  = ball.GetX();
    float ballRight = ball.GetX() + BALL_WIDTH;
    float ballTop   = ball.GetY();
    float ballBot   = ball.GetY() + BALL_HEIGHT;

    float paddleLeft  = paddle.GetX();
    float paddleRight = paddle.GetX() + PADDLE_WIDTH;
    float paddleTop   = paddle.GetY();
    float paddleBot   = paddle.GetY() + PADDLE_HEIGHT;

    Contact contact{};

    // non contact collisions
    if(ballLeft >= paddleRight)
    {
        return contact;
    }
    else if (ballRight <= paddleLeft)
    {
        return contact;
    }
    else if (ballTop >= paddleBot)
    {
        return contact;
    }
    else if (ballBot <= paddleTop)
    {
        return contact;
    }

    float paddleRangeUpper  = paddleBot - (2.0f * PADDLE_HEIGHT / 3.0f);
    float paddleRangeMiddle = paddleBot - (PADDLE_HEIGHT / 3.0f);

    if (ball.m_velocity.GetX() < 0)
    {   // left paddle
        contact.penetration = paddleRight - ballLeft;
    }
    else if (ball.m_velocity.GetX() > 0)
    {   // right paddle
        contact.penetration = paddleLeft - ballRight;
    }

    if ((ballBot > paddleTop) && (ballBot < paddleRangeUpper))
    {
        contact.type = CollisionType::Top;
    }
    else if ((ballBot > paddleTop) && (ballBot < paddleRangeMiddle))
    {
        contact.type = CollisionType::Middle;
    }
    else
    {
        contact.type = CollisionType::Bottom;
    }
    return contact;
}

Contact CheckWallCollision (Ball const& ball)
{
    float ballLeft  = ball.GetX();
    float ballRight = ball.GetX() + BALL_WIDTH;
    float ballTop   = ball.GetY();
    float ballBot   = ball.GetY() + BALL_HEIGHT;

    Contact contact{};

    if (ballLeft < 0.0f)
    {
        contact.type = CollisionType::Left;
    }
    else if (ballRight > WINDOW_WIDTH)
    {
        contact.type = CollisionType::Right;
    }
    else if (ballTop < 0.0f)
    {
        contact.type = CollisionType::Top;
        contact.penetration = - ballTop;
    }
    else if (ballBot > WINDOW_HEIGHT)
    {
        contact.type = CollisionType::Bottom;
        contact.penetration = WINDOW_HEIGHT - ballBot;
    }

    return contact;
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Window   *window    = SDL_CreateWindow("My pong",0,0,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer  = SDL_CreateRenderer(window,-1,0);

    //Initializing fonts and player score
    TTF_Font     *scorefont = TTF_OpenFont("media/DejaVuSansMono.ttf", 40);

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

    //initialize sound effects
    Mix_Chunk *wallHitSound   = Mix_LoadWAV("media/WallHit.wav");
    Mix_Chunk *paddleHitSound = Mix_LoadWAV("media/PaddleHit.wav");            


    {   //game logic
        int playerOnescore = 0;
        int playerTwoscore = 0;

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


            //check collisions
            if (Contact contact = CheckPaddleCollision(ball, paddleOne); contact.type != CollisionType::None)
            {
                ball.CollideWithPaddle(contact);
                Mix_PlayChannel(-1, paddleHitSound, 0);

            }
            else if (Contact contact = CheckPaddleCollision(ball, paddleTwo); contact.type != CollisionType::None)
            {
                ball.CollideWithPaddle(contact);
                Mix_PlayChannel(-1, paddleHitSound, 0);

            }
            else if (Contact contact = CheckWallCollision(ball); contact.type != CollisionType::None)
            {
                ball.CollideWithWall(contact);

                if(contact.type == CollisionType::Left)
                {
                    ++playerTwoscore;
                    playerTwoScoreText.SetScore(playerTwoscore);
                }
                else if (contact.type == CollisionType::Right)
                {
                    ++playerOnescore;
                    playerOneScoreText.SetScore(playerOnescore);
                }
                else
                {
                    Mix_PlayChannel(-1, wallHitSound, 0);
                }
            }
        }
    }

    Mix_FreeChunk(wallHitSound);
    Mix_FreeChunk(paddleHitSound);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(scorefont);
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}