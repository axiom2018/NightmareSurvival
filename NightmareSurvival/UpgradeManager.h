// UpgradeManager.h
#pragma once
#include <vector>

// Manages activity when player uses upgrades like ammunition, health etc.

class UpgradeManager
{
    class UpgradeStrategy *m_pUpgradeStrategy;
    class Items *m_pItem;
    int m_index;
    bool FindUpgrade(std::vector<class Items*> * pInventory, int itemID);
public:
    UpgradeManager();
    void UseUpgrade(int itemID, std::vector<class Items*> * pInventory, class WeaponManager *pWeaponManager);
    ~UpgradeManager();
};