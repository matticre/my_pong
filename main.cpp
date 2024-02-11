#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "include/Ball.h"
#include "include/Paddle.h"
#include "include/Constants.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My pong");
    window.setVerticalSyncEnabled(true); 

    Ball ball(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
              sf::Vector2f(0,0));
    
    Paddle paddleOne(sf::Vector2f(50.0f, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2), sf::Vector2f(0,0));
    Paddle paddleTwo(sf::Vector2f(WINDOW_WIDTH - 50.0f, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2), sf::Vector2f(0,0));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        window.clear(sf::Color::Black);
        ball.Draw(window);
        paddleOne.Draw(window);
        paddleTwo.Draw(window);

        window.display();
    } 



    return 0;
}
