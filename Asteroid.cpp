#include "Asteroid.h"
#include "utils.h"

Asteroid::Asteroid(int x, int y, float speed, int angle, int health, int size, int color)
{

    int coords[3][3][12] = {
        {
            {0, 0, 71, 66, 0, 76, 67, 74, 0, 162, 68, 71},
            {71, 0, 71, 66, 71, 76, 67, 74, 71, 162, 68, 71},
            {150, 162, 68, 71, 150, 162, 68, 71, 150, 162, 68, 71}
        },
        {

            {145, 0, 34, 34, 145, 34, 34, 34, 145, 68, 34, 34},
            {145 + 34, 0, 34, 34, 145 + 34, 34, 34, 34, 145 + 34, 72, 34, 34},
            {145 + 68, 0, 34, 34, 145 + 68, 34, 34, 34, 145 + 68, 72, 34, 34}
        },
        {

            {145, 110, 21, 21, 145, 131, 21, 21, 145, 131, 21, 21},
            {145 + 21, 110, 21, 21, 145 + 21, 131, 21, 21, 145 + 21, 131, 21, 21},
            {145 + 42, 110, 21, 21, 145 + 42, 131, 21, 21, 145 + 42, 131, 21, 21}
        }
    };

    m_texture.loadFromFile("asteroids.png");
    m_sprite.setTexture(m_texture);
    int i = int(rnd(3)) * 4;
    m_sprite.setTextureRect(sf::IntRect(coords[size][color][i], coords[size][color][i+1], coords[size][color][i+2], coords[size][color][i+3]));
    if(size == 0){
        m_sprite.setOrigin(35, 35);
    } else if(size == 1){
        m_sprite.setOrigin(17, 17);

    } else {
        m_sprite.setOrigin(10, 10);

    }
    m_x = x;
    m_y = y;
    m_delta_x = 0;
    m_delta_y = 0;
    m_angle = angle;
    m_health = health;
    m_size = size;
    m_color = color;
    forward(speed);
}

bool Asteroid::hit(void)
{
    m_health--;
    if(m_health == 0) return true;
    return false;
}
