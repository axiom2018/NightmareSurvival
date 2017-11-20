// WeaponManager.h
#pragma once
#include <string>
#include <vector>

// Manages weapon related activity such as getting current weapon name, ammunition, open inventory, shoot, etc.

class WeaponManager
{
    class Items *m_pPlayerCurrentWeapon;
    class WeaponsFactory *m_pWF;
    class CycleWeapons *m_pCycleInventory;
    int m_shootingCoolDown;

    bool CheckCoolDown();
    bool CheckAmmo(int weaponAmmo) const;
public:
    WeaponManager();
    void SetWeapon(class Items *pWeapon);
    class Items * GetCurrentWeapon() const;
    std::string WeaponName() const;
    int GetWeaponAmmunition() const;
    void SetWeaponAmmunition(int ammo);
    void OpenWeaponInventory(std::vector<class Items*> pInventory);
    void ShootWeapon();
    ~WeaponManager();
};