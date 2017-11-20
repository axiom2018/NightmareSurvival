// AmmoStrategy.cpp
#include "AmmoStrategy.h"
#include "Items.h"
#include "WeaponManager.h"
#include "World.h"
#include "Player.h"

// Use the WeaponManager.
void AmmoStrategy::Use(class Items * pItem, WeaponManager * pWeaponManager)
{
    // Step 1. Get ammo.
    int ammo = pWeaponManager->GetWeaponAmmunition();

    // Step 2. Use item.
    int upgradeAmount = pItem->GetUpgradeAmount();

    // Step 3. Add upgrade amount to ammunition.
    int total = ammo + upgradeAmount;

    // Step 4. Set ammo.
    pWeaponManager->SetWeaponAmmunition(total);

    // Step 5. Delete item.
    delete pItem;
    pItem = nullptr;
}
