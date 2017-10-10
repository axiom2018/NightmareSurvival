// CycleInventory.h
#pragma once
#include <vector>

class CycleWeapons
{
private:
    std::vector<class Items*> m_pValidWeapons;
    class InventoryManager *m_pIManager;
    char m_cursor;
    char m_marker;
    int m_currentChosenIndex;
    int m_playerInventorySize;
    int m_verifiedWeaponary;

    bool CheckWeaponSize();
    void NormalCursorMovement(int *pIndex, char direction);
    void MoveCursorDown(int *pIndex, char direction);
    void MoveCursorUp(int *pIndex, char direction);
    void Selection(int *pIndex, char direction);
    void ProcessWeapons(std::vector<class Items*> pPlayerInventory);
    bool ProcessPlayerInput(char input);
    void DisplayWeapons();
public:
    CycleWeapons(class InventoryManager *pIManager);
    bool WeaponryGUI(std::vector<class Items*> pInventory, class Items &pPlayerCurrentWeapon);
    ~CycleWeapons() {};
};

