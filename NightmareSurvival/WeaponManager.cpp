// WeaponManager.cpp
#include "WeaponManager.h"
#include "WeaponsFactory.h"
#include "CycleWeapons.h"
#include "BulletManager.h"
#include "Items.h"
#include "World.h"
#include <iostream>

WeaponManager::WeaponManager()
{
    // Step 1. Set to nullptr.
    m_pPlayerCurrentWeapon = nullptr;

    // Step 2. Init cycle weapons.
    m_pCycleInventory = new CycleWeapons(this);

    // Step 3. Init weapons factory.
    m_pWF = new WeaponsFactory;

    // Step 4. Set cooldown to 2.
    m_shootingCoolDown = 2;

    // Step 5. Set player current weapon.
    m_pPlayerCurrentWeapon = m_pWF->GetItem(0);
}

void WeaponManager::SetWeapon(Items * pWeapon)
{
    m_pPlayerCurrentWeapon = pWeapon;
}

// Referenced in InventoryManager.
Items * WeaponManager::GetCurrentWeapon() const
{
    return m_pPlayerCurrentWeapon;
}

// Referenced in Player.cpp.
std::string WeaponManager::WeaponName() const
{
    return m_pPlayerCurrentWeapon->ItemName();
}

// Referenced in Player.cpp.
int WeaponManager::GetWeaponAmmunition() const
{
    return m_pPlayerCurrentWeapon->GetAmmo(); 
}

// Referenced in Player.cpp.
void WeaponManager::SetWeaponAmmunition(int ammo)
{
    m_pPlayerCurrentWeapon->SetAmmo(ammo);
}

// In order to fire the weapon, the cooldown must be 0.
bool WeaponManager::CheckCoolDown()
{
    if (m_shootingCoolDown == 0)
        return true;

    --m_shootingCoolDown;

    return false;
}

// If ammo is 0, obviously no shooting will be done.
bool WeaponManager::CheckAmmo(int weaponAmmo) const
{
    if (weaponAmmo == 0)
    {
        std::cout << " Reload immediately!\n";
        return true;
    }

    return false;
}

void WeaponManager::OpenWeaponInventory(std::vector<class Items*> pInventory)
{
    // Step 1. Save inventory size.
    int inventorySize = pInventory.size();

    // Step 2. Save amount of total weapons.
    int maxWeapons = 0;

    // Step 3. Get ID's of each entity in inventory and see if they are weapons and not upgrades.
    for (int i = 0; i < inventorySize; ++i)
    {
        if (ItemsFactory::WeaponIDCheck(pInventory.at(i)->GetId()))
            ++maxWeapons;
    }

    // Step 4. If player has more than 1 weapon, proceed with opening inventory.
    if (maxWeapons > 1)
    {
        m_pCycleInventory->WeaponryGUI(pInventory, *m_pPlayerCurrentWeapon);
        return;
    }

    // (Optional Step) If Step 3 is false, alert the player to get more weapons in their arsenal.
    std::cout << " You only have 1 weapon! Get more weapons!\n";
}

void WeaponManager::ShootWeapon()
{
    // Step 1. If cooldown is not at 0, do not continue with function.
    if (!CheckCoolDown())
        return;

    // Step 2. If weapon is out of ammunition, do not continue with function.
    if (CheckAmmo(m_pPlayerCurrentWeapon->GetAmmo()))
        return;

    // Step 3. Carry out shooting commands.
    World::Instance()->GetBulletManager()->RequestBullet(m_pPlayerCurrentWeapon->GetId());

    // Step 4. Decrease ammo and reset cooldown.
    m_pPlayerCurrentWeapon->DecreaseAmmo();

    // Step 5. Reset cool down.
    m_shootingCoolDown = 2;
}

WeaponManager::~WeaponManager()
{
    delete m_pCycleInventory;
    m_pCycleInventory = nullptr;

    delete m_pWF;
    m_pWF = nullptr;
}
