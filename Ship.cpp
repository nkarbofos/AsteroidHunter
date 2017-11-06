#include "Ship.h"

Ship::Ship(int x, int y)
{
    m_texture.loadFromFile("mship1.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(x, y);
    m_x = x;
    m_y = y;
    m_angle = 0;
    m_sprite.setOrigin(36, 35);
    m_delta_x = 0;
    m_delta_y = 0;
}

void Ship::left(void)
{
    m_angle -= 5;
}

void Ship::right(void)
{
    m_angle += 5;
}
