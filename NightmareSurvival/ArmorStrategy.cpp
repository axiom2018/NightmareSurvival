// ArmorStrategy.cpp
#include "ArmorStrategy.h"
#include "ArmorManager.h"
#include "Items.h"
#include "World.h"
#include "Player.h"

// No need to use the WeaponManager, use the Player's interface to alter ammunition.
void ArmorStrategy::Use(class Items * pItem, WeaponManager * pWeaponManager)
{
    // Step 1. Get armor value from player.
    int armor = World::Instance()->GetPlayer()->GetArmorManager()->GetArmor();

    // Step 2. Use item.
    int upgradeAmount = pItem->GetUpgradeAmount();

    // Step 3. Add upgrade amount to armor.
    int total = armor + upgradeAmount;

    // Step 4. Set the armor value.
    World::Instance()->GetPlayer()->GetArmorManager()->SetArmor(total);

    // Step 5. Delete item.
    delete pItem;
    pItem = nullptr;
}
