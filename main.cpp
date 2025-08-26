#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>
#include "include/Ball.h"
#include "include/Paddle.h"
#include "include/Constants.h"
#include "include/Net.h"
#include "include/Score.h"
#include "include/Menu.h"
#include <iostream>
#include <chrono>
#include <random>

enum Buttons
{
    PaddleOneUp,
    PaddleOneDown,
    PaddleTwoUp,
    PaddleTwoDown,
};

Contact checkPaddleCollision(const Ball &ball, const Paddle &paddle)
{
    float ballLeft  = ball.GetPosition().x;
    float ballRight = ball.GetPosition().x + BALL_WIDTH;
    float ballTop   = ball.GetPosition().y;
    float ballBot   = ball.GetPosition().y + BALL_HEIGHT;

    float paddleLeft  = paddle.GetPosition().x;
    float paddleRight = paddle.GetPosition().x + PADDLE_WIDTH; 
    float paddleTop   = paddle.GetPosition().y;
    float paddleBot   = paddle.GetPosition().y + PADDLE_HEIGHT;

    Contact contact{};

    //non-contact collisions
    if (ballRight <= paddleLeft){
        return contact;
    }
    else if (ballLeft >= paddleRight){
        return contact;
    }
    else if (ballBot <= paddleTop){
        return contact;
    }
    else if (ballTop >= paddleBot){
        return contact;
    }

    float paddleUpRange     = paddleBot - 2 * PADDLE_HEIGHT / 3;
    float paddleMiddleRange = paddleBot - PADDLE_HEIGHT / 3;

    if (ball.GetVx() < 0){
        contact.penetration = paddleRight - ballLeft; 
    }
    else if (ball.GetVx() > 0){
        contact.penetration = paddleLeft - ballRight; 
    } 

    if ((ballBot > paddleTop) && (ballBot < paddleUpRange)){
        contact.type = CollisionType::Top;
    }
    else if ((ballBot > paddleTop) && (ballBot < paddleMiddleRange)){
        contact.type = CollisionType::Middle;
    }
    else {
        contact.type = CollisionType::Bot;
    }

    return contact;
}

Contact checkWallCollision (const Ball &ball)
{
    float ballLeft  = ball.GetPosition().x;
    float ballRight = ball.GetPosition().x + BALL_WIDTH;
    float ballTop   = ball.GetPosition().y;
    float ballBot   = ball.GetPosition().y + BALL_HEIGHT;

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
        contact.penetration = -ballTop;
    }
    else if (ballBot > WINDOW_HEIGHT)
    {
        contact.type = CollisionType::Bot;
        contact.penetration = WINDOW_HEIGHT - ballBot;
    }

    return contact;
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0,1);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My pong");
    sf::SoundBuffer wallBuffer, paddleBuffer;
    wallBuffer.loadFromFile("./media/WallHit.wav");
    paddleBuffer.loadFromFile("./media/PaddleHit.wav");

    sf::Sound hitWallSound, hitPaddleSound;
    hitWallSound.setBuffer(wallBuffer);
    hitPaddleSound.setBuffer(paddleBuffer);

    Ball ball(sf::Vector2f(WINDOW_WIDTH / 2 - BALL_WIDTH / 2, WINDOW_HEIGHT / 2 - BALL_HEIGHT / 2),
              sf::Vector2f(0.0f,0.0f));  
    Paddle paddleOne(sf::Vector2f(PADDLE_ONE_X, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2), sf::Vector2f(0,0));
    Paddle paddleTwo(sf::Vector2f(PADDLE_TWO_X, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2), sf::Vector2f(0,0));
    Score scoreOne(WINDOW_WIDTH * 0.25);
    Score scoreTwo(WINDOW_WIDTH * 0.75);

    Net net(WINDOW_WIDTH / 2);
    Net goalNetOne(PADDLE_ONE_X);
    Net goalNetTwo(PADDLE_TWO_X);

    Menu menu;

    float dt = 0.0f;
    bool buttons[4] = {};

    bool runMenu = true;
    bool runGame = true;

    while(runMenu)
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    runMenu = false;
                    runGame = false;
                }   
                else if (event.key.code == sf::Keyboard::Up)
                {
                    menu.MoveUp();
                    menu.Draw(window);
                    window.display();
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    menu.MoveDown();
                    menu.Draw(window);
                    window.display();    
                }

                menu.Select(event, runMenu, runGame);
            }
        }


        window.clear(sf::Color::Black);
        menu.Draw(window);
        window.display();    
    }

    while (runGame)
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                runGame = false;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    runGame = false;
                }
                else if (event.key.code == sf::Keyboard::W)
                {
                    buttons[Buttons::PaddleOneUp] = true;
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    buttons[Buttons::PaddleOneDown] = true;
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    buttons[Buttons::PaddleTwoUp] = true;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    buttons[Buttons::PaddleTwoDown] = true;
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    if (ball.GetVelocity() == sf::Vector2f(0.0f,0.0f))
                    {
                        if (scoreOne.GetScore() > scoreTwo.GetScore())
                        {
                            ball.SetVx(BALL_SPEED);
                        } 
                        else if (scoreOne.GetScore() < scoreTwo.GetScore())
                        {
                            ball.SetVx(-BALL_SPEED);
                        }
                        else 
                        {
                            float num = dis(gen);
                            if(num > 0.5)
                            {
                                ball.SetVx(BALL_SPEED);
                            }
                            else 
                            {
                                ball.SetVx(-BALL_SPEED);
                            }
                        }
                    }
                }
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::W)
                {
                    buttons[Buttons::PaddleOneUp] = false;
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    buttons[Buttons::PaddleOneDown] = false ;
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    buttons[Buttons::PaddleTwoUp] = false;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    buttons[Buttons::PaddleTwoDown] = false ;
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
        
        if(Contact contact = checkPaddleCollision(ball, paddleOne); contact.type != CollisionType::None)
        {
            ball.CollideWithPaddle(contact);
            hitPaddleSound.play();
        }
        else if(Contact contact = checkPaddleCollision(ball, paddleTwo); contact.type != CollisionType::None)
        {
            ball.CollideWithPaddle(contact);
            hitPaddleSound.play();
        }

        if(Contact contact = checkWallCollision(ball); contact.type != CollisionType::None)
        {
            ball.CollideWithWall(contact);
            hitWallSound.play();

            if (contact.type == CollisionType::Left)
            {
                scoreTwo.Increase();
            }
            else if (contact.type == CollisionType::Right)
            {
                scoreOne.Increase();
            }
        }

        auto stopTime = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime-startTime).count();
        
        //Update
        ball.Update(dt);
        paddleOne.Update(dt);
        paddleTwo.Update(dt);
        
        window.clear(sf::Color::Black);
        ball.Draw(window);
        paddleOne.Draw(window);
        paddleTwo.Draw(window);
        net.Draw(window);
        goalNetOne.Draw(window);
        goalNetTwo.Draw(window);
        scoreOne.Draw(window);
        scoreTwo.Draw(window); 
      
        window.display();
    }

    window.close();

    return 0;
}
