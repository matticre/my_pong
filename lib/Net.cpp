#include "../include/Net.h"

void Net::Draw(sf::RenderWindow &window){
    for (int i = 0; i < WINDOW_HEIGHT; ++i){
        if ( i % 20 < 10){
            sf::Vertex point(sf::Vector2f(m_x, i), sf::Color::White);
            window.draw(&point, 1, sf::Points);
        }
    }
}