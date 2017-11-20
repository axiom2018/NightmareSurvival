// CycleInventory.h
#pragma once
#include <vector>

// Manage how player goes through weapons.

class CycleWeapons
{
private:
    std::vector<class Items*> m_pValidWeapons;
    class WeaponManager *m_pWeaponManager;
    class CursorManager *m_pCursorManager;
    char m_cursor;
    char m_marker;
    int m_currentChosenIndex;
    int m_playerInventorySize;
    int m_verifiedWeaponary;

    void SetWeapon();
    void CheckWeaponSize();
    void ProcessWeapons(std::vector<class Items*> pPlayerInventory);
    void DisplayWeapons();
public:
    CycleWeapons(class WeaponManager *pWeaponManager);
    void WeaponryGUI(std::vector<class Items*> pInventory, class Items &pPlayerCurrentWeapon);
    ~CycleWeapons();
};

