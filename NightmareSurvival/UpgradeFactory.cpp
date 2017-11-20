// UpgradeFactory.cpp
#include "UpgradeFactory.h"
#include "FirstAid.h"
#include "Armor.h"
#include "Ammo.h"

Items * UpgradeFactory::GetItem(int choice)
{
    switch (choice)
    {
    case 0:
        return new FirstAid;
    case 1:
        return new Armor;
    case 2:
        return new Ammo;
    default:
        break;
    }

    return nullptr;
}