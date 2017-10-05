// Bullets.cpp
#include "Bullets.h"
#include "PistolBullet.h"
#include "ShotgunBullet.h"
#include "Rocket.h"
#include "Entities.h"

#define MAX_BULLETS 3

Entities * Bullets::GetBullet(int type)
{
    switch (type)
    {
    case 0:
        return new PistolBullet;
    case 1:
        return new ShotgunBullet;
    case 2:
        return new Rocket;
    default:
        break;
    }

    return nullptr;
}
