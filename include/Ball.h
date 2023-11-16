#ifndef BALL_H
#define BALL_H  

#include "Vec2.h"
#include <SDL2/SDL.h>

class Ball
{
    public:
        Ball(Vec2 position,Vec2 velocity, int width, int height):
            m_position(position), m_velocity(velocity), m_width(width), m_height(height)
        {
            rect.x = static_cast<int>(position.GetX());
            rect.y = static_cast<int>(position.GetY());
            rect.w = m_width;        
            rect.h = m_height;
        };

        void Draw(SDL_Renderer *renderer)
        {
            SDL_RenderFillRect(renderer, &rect);
        }


    private:
        Vec2 m_position;
        Vec2 m_velocity;
        int  m_width;
        int  m_height;
        SDL_Rect rect;

};


#endif