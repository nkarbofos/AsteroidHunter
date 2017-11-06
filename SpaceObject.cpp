#include <math.h>
#include "SpaceObject.h"

#define PI 3.14159265

void SpaceObject::set_angle(int angle)
{
    m_angle = angle;
}


void SpaceObject::forward(float step)
{
    float delta_x = sin(m_angle*PI/180);
    float delta_y = -cos(m_angle*PI/180);

    m_delta_x += step*delta_x;
    m_delta_y += step*delta_y;
}

void SpaceObject::update(void)
{
    m_sprite.setPosition(m_x, m_y);
    m_sprite.setRotation(m_angle);
    m_x += m_delta_x;
    m_y += m_delta_y;
    if(m_x>840) m_x = -40;
    if(m_y>640) m_y = -40;
    if(m_x<-40) m_x = 840;
    if(m_y<-40) m_y = 640;
    m_frame_cnt++;
}

sf::Sprite &SpaceObject::get_sprite(void)
{
    return m_sprite;
}
