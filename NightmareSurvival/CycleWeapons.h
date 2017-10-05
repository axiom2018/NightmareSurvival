// CycleInventory.h
#pragma once
#include "PlayerAlgorithms.h"

class CycleWeapons : public PlayerAlgorithms
{
private:
    class Player *m_pPlayer;
    std::vector<class Items*> m_pValidWeapons;
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
    void DisplayPlayerWeapons();
public:
    CycleWeapons(class Player *player);
    virtual bool CycleWeaponry(std::vector<class Items*> pPlayerInventory, class Items &pPlayerCurrentWeapon) override;
    ~CycleWeapons() {};
};

