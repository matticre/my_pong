#ifndef PADDLE_H
#define PADDLE_H

class Paddle
{
    public:
        Paddle(Vec2 position,Vec2 velocity, int width, int height):
            m_position(position), m_velocity(velocity), m_width(width), m_height(height)
        {
            rect.x = position.GetX();
            rect.y = position.GetY();
            rect.w = m_width;
            rect.h = m_height;
        };

        void Draw(SDL_Renderer *render)
        {
            SDL_RenderFillRect(render, &rect);
        }

    private:
        Vec2 m_position;
        Vec2 m_velocity;
        int  m_width;
        int  m_height;
        SDL_Rect rect;

};


#endif