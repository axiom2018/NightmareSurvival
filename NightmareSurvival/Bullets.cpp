// Bullets.cpp
#include "Bullets.h"
#include "PistolBullet.h"
#include "ShotgunBullet.h"
#include "Rocket.h"
#include "Entities.h"
#include "Definitions.h"

Entities * Bullets::GetBullet(int type)
{
    switch (type)
    {
    case PISTOL_BULLET:
        return new PistolBullet;
    case SHOTGUN_BULLET:
        return new ShotgunBullet;
    case ROCKET:
        return new Rocket;
    default:
        break;
    }

    return nullptr;
}
