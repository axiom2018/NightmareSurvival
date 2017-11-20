// InventoryManager.h
#pragma once
#include <vector>

// Interface to the inventory system for the player.

class InventoryManager
{
    std::vector<class Items*> m_pInventory;
    class WeaponManager *m_pWeaponManager;
    class UpgradeManager *m_pUpgradeManager;
public:
    InventoryManager();
    class WeaponManager * GetWeaponManager() const;
    std::string GetWeaponName() const;
    int GetWeaponAmmunition() const; 
    void AddToInventory(class Items *pItem);
    void OpenInventory(); 
    void SetPlayerCurrentWeapon(class Items *pWeapon); 
    void ShootWeapon(); 
    void UseUpgrade(int itemID);
    ~InventoryManager();
};