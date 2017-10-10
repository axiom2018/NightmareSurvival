// InventoryManager.h
#pragma once
#include <vector>

// Interface to the inventory system for the player.

class InventoryManager
{
    std::vector<class Items*> m_pInventory;
    class WeaponsFactory *m_pWF;
    class CycleWeapons *m_pCycleInventory;
    class Items *m_pCurrentWeapon;
    class CurrentWeaponManager *m_pCurrentWeaponManager;
public:
    InventoryManager();
    int GetInventorySize() const;
    std::string GetWeaponName() const;
    int GetWeaponAmmunition() const;
    void AddToInventory(class Items *pItem);
    void OpenInventory();
    void SetPlayerCurrentWeapon(class Items *pWeapon);
    void ShootWeapon();
    ~InventoryManager();
};