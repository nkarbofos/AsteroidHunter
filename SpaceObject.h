#ifndef SPACEOBJECT_H_INCLUDED
#define SPACEOBJECT_H_INCLUDED

#include <SFML/Graphics.hpp>

class SpaceObject
{
protected:
    float m_x, m_y;
    float m_delta_x, m_delta_y;
    int m_angle;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    int m_frame_cnt;
public:
    SpaceObject(void)
    {
        m_frame_cnt = 0;
    }
    void forward(float step);
    void update(void);
    void set_angle(int angle);
    sf::Sprite &get_sprite(void);
    int get_x(void)
    {
        return m_x;
    }
    int get_y(void)
    {
        return m_y;
    }
    int get_angle(void)
    {
        return m_angle;
    }
};


#endif // SPACEOBJECT_H_INCLUDED
