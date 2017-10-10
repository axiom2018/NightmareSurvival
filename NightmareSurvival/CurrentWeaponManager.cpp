// CurrentWeaponManager.cpp
#include "CurrentWeaponManager.h"
#include "Items.h"
#include "BulletManager.h"
#include <iostream>

CurrentWeaponManager::CurrentWeaponManager()
{
    // Step 1. Set to nullptr.
    m_pPlayerCurrentWeapon = nullptr;

    // Step 2. Init bullet manager.
    m_pBulletManager = new BulletManager;

    // Step 2. Set cooldown to 2.
    m_shootingCoolDown = 2;
}

// In order to fire the weapon, the cooldown must be 0.
bool CurrentWeaponManager::CheckCoolDown()
{
    if (m_shootingCoolDown == 0)
        return true;

    --m_shootingCoolDown;

    return false;
}

// If ammo is 0, obviously no shooting will be done.
bool CurrentWeaponManager::CheckAmmo(int weaponAmmo) const
{
    if (weaponAmmo == 0)
    {
        std::cout << " Reload immediately!\n";
        return true;
    }

    return false;
}

void CurrentWeaponManager::SetWeapon(Items * pWeapon)
{
    m_pPlayerCurrentWeapon = pWeapon;
}

void CurrentWeaponManager::ShootWeapon()
{
    // Step 1. If cooldown is not at 0, do not continue with function.
    if (!CheckCoolDown())
        return;

    // Step 2. If weapon is out of ammunition, do not continue with function.
    if (CheckAmmo(m_pPlayerCurrentWeapon->GetAmmo()))
        return;

    // Step 3. Carry out shooting commands.
    m_pBulletManager->RequestBullet(m_pPlayerCurrentWeapon->GetId());

    // Step 4. Decrease ammo and reset cooldown.
    m_pPlayerCurrentWeapon->DecreaseAmmo();

    // Step 5. Reset cool down.
    m_shootingCoolDown = 2;
}

CurrentWeaponManager::~CurrentWeaponManager()
{
    delete m_pBulletManager;
    m_pBulletManager = nullptr;
}
