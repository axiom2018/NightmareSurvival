// PistolBullet.cpp
#include "PistolBullet.h"

PistolBullet::PistolBullet() :
    m_bullet('+'),
    m_x(0),
    m_y(0)
{

}

void PistolBullet::Update()
{
    switch (m_direction)
    {
    case Directions::West:
        m_y -= 1;
        break;
    case Directions::North:
        m_x -= 1;
        break;
    case Directions::East:
        m_y += 1;
        break;
    case Directions::South:
        m_x += 1;
        break;
    default:
        return;
    }
}