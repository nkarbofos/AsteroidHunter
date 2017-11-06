#include "Explosion.h"

Explosion::Explosion(int x, int y)
{
    m_texture.loadFromFile("explosion.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
    m_sprite.setPosition(x, y);
    m_sprite.setOrigin(25, 25);
    cut_x = 0;
    cut_y = 0;
    cut_cnt = 0;
}

void Explosion::update(void)
{
    m_sprite.setTextureRect(sf::IntRect(cut_x, cut_y, 50, 50));
    if(cut_x > 350)
    {
        cut_x = 50;
        cut_y += 50;
    }
    else cut_x += 50;
}

bool Explosion::is_alive(void)
{
    if(cut_y > 350) return false;
    return true;
}
