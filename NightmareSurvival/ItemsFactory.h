// ItemsFactory.h
#pragma once
#include "Items.h"

/* Abstract factory pattern design followed. (https://sourcemaking.com/design_patterns/abstract_factory/cpp/1) In the link above the "Factory" 
class they have is the same concept as the ItemsFactory.h/.cpp files. Just like their "MotifFactory" class. I have a WeaponsFactory.h/.cpp. Like
their "WindowsFactory" class. */

class ItemsFactory
{
public:
    virtual Items *GetItem(int choice) = 0;
    static bool WeaponIDCheck(int weaponID);
    static bool UpgradeIDCheck(int upgradeID);
};