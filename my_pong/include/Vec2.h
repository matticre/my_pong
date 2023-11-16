#ifndef VEC2_H
#define VEC2_H

class Vec2
{   
    public:
        Vec2(): 
            m_x(0x0f), m_y(0.0f){};

        Vec2(float x, float y):
            m_x(x), m_y(y){};

        float GetX() {return m_x;};

        float GetY() {return m_y;};
        
        void  SetX(const float &x) {m_x = x;};
        
        void  SetY(const float &y) {m_y = y;};

        Vec2 operator+(Vec2 const &vec)
        {
            return Vec2(m_x + vec.m_x , m_y + vec.m_y);
        };

        Vec2& operator+=(Vec2 const &vec)
        {
            m_x += vec.m_x;
            m_y += vec.m_y;

            return *this;
        };

        Vec2 operator*(const float &c)
        {
            return Vec2(c* m_x, c*m_y);
        };

    private:
        float m_x;
        float m_y;
};


#endif