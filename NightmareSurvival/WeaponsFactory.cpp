// WeaponsFactory.cpp
#include "WeaponsFactory.h"
#include "Pistol.h"
#include "Shotgun.h"
#include "RocketLauncher.h"

// Factory pattern for game weaponry.

Items *WeaponsFactory::GetItem(int choice)
{
    switch (choice)
    {
    case 0:
        return new Pistol;
    case 1:
        return new Shotgun;
    case 2:
        return new RocketLauncher;
    default:
        break;
    }

    return nullptr;
}
