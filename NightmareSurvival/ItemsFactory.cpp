// ItemsFactory.cpp
#include "ItemsFactory.h"
#include "Ammo.h"
#include "Armor.h"
#include "FirstAid.h"
#include "Pistol.h"
#include "Shotgun.h"
#include "RocketLauncher.h"

// Check ID of weapon to proceed.

bool ItemsFactory::WeaponIDCheck(int weaponID)
{
    switch (weaponID)
    {
    case PISTOL_ID:
        return true;
    case SHOTGUN_ID:
        return true;
    case ROCKET_LAUNCHER_ID:
        return true;
    default:
        break;
    }

    return false;
}
