#include "Bullet.h"

Bullet::Bullet(int x, int y, int angle, sf::Texture &t)
{
    m_sprite.setTexture(t);
    m_sprite.setPosition(x, y);
    m_x = x;
    m_y = y;
    m_angle = angle;
    m_sprite.setOrigin(10, 15);
    m_delta_x = 0;
    m_delta_y = 0;
    forward(10);
}
