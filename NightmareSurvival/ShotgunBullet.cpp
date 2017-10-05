// ShotgunBullet.cpp
#include "ShotgunBullet.h"

ShotgunBullet::ShotgunBullet() :
    m_bullet('@'),
    m_x(0),
    m_y(0),
    m_damage(10)
{

}

void ShotgunBullet::Update()
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
        std::cout << "Error! [ShotgunBullet.cpp]\n";
    }
}