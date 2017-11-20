// FirstAidStrategy.cpp
#include "FirstAidStrategy.h"
#include "HealthManager.h"
#include "Items.h"
#include "World.h"
#include "Definitions.h"
#include "Player.h"

// No need to use the WeaponManager, use the Player's interface to alter health.
void FirstAidStrategy::Use(class Items * pItem, WeaponManager * pWeaponManager)
{
    // Step 1. Get health value from player.
    int health = World::Instance()->GetPlayer()->GetHealthManager()->GetHealth();

    // Step 2. Use item.
    int upgradeAmount = pItem->GetUpgradeAmount();

    // Step 3. Add upgrade amount to armor.
    int total = health + upgradeAmount;

    // Step 4. Always cap health at 80.
    if (total > PLAYER_HEALTH)
    {
        total = PLAYER_HEALTH;
    }

    // Step 5. Set the armor value.
    World::Instance()->GetPlayer()->GetHealthManager()->SetHealth(total);

    // Step 5. Delete item.
    delete pItem;
    pItem = nullptr;
}
