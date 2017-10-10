// CurrentWeaponManager.h
#pragma once

/* The current weapon of the player is stored in the InventoryManager.h file, but that InventoryManager.h/.cpp interface is solely for 
handling the inventory. CurrentWeaponManager.h will take on requests to work with whatever current weapon the player is using and carry out
functions regarding that weapon. */

class CurrentWeaponManager
{
    class Items *m_pPlayerCurrentWeapon;
    class BulletManager *m_pBulletManager;
    int m_shootingCoolDown;

    bool CheckCoolDown();
    bool CheckAmmo(int weaponAmmo) const;
public:
    CurrentWeaponManager();
    void SetWeapon(class Items *pWeapon);
    void ShootWeapon();
    ~CurrentWeaponManager();
};