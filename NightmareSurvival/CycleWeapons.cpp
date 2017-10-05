// CycleWeapons.cpp
#include "CycleWeapons.h"
#include "ItemsFactory.h"
#include <iostream>
#include <string>
#include <conio.h>
#include "Player.h"

CycleWeapons::CycleWeapons(class Player *player) :
    m_cursor('S'),
    m_marker(' '),
    m_currentChosenIndex(0)
{
    m_pPlayer = player;
}

bool CycleWeapons::CheckWeaponSize()
{
    if (m_pValidWeapons.empty())
        return false;

    m_pValidWeapons.clear();

    return true;
}

void CycleWeapons::NormalCursorMovement(int *pIndex, char direction)
{
    switch (direction)
    {
    case 'w':
        *pIndex -= 1;
        break;
    case 's':
        *pIndex += 1;
        break;
    default:
        std::cout << "Invalid direction! [NormalCursorMovement]";
        break;
    }
}

void CycleWeapons::MoveCursorDown(int *pIndex, char direction)
{
    switch (direction)
    {
    case 'w':
        *pIndex -= 1;
        break;
    case 's':
        *pIndex = 0;
        break;
    default:
        std::cout << "Invalid direction! [MoveCursorDown]";
        break;
    }
}

void CycleWeapons::MoveCursorUp(int *pIndex, char direction)
{
    switch (direction)
    {
    case 'w':
        *pIndex = m_verifiedWeaponary - 1;
        break;
    case 's':
        *pIndex += 1;
        break;
    default:
        std::cout << "Invalid direction! [MoveCursorTop]";
        break;
    }
}

void CycleWeapons::Selection(int *pIndex, char direction)
{
    if (*pIndex == 0)
    {
        MoveCursorUp(pIndex, direction);
        return;
    }

    else if (*pIndex == m_verifiedWeaponary - 1)
    {
        MoveCursorDown(pIndex, direction);
        return;
    }

    NormalCursorMovement(pIndex, direction);
}

void CycleWeapons::ProcessWeapons(std::vector<class Items*> pPlayerInventory)
{
    m_playerInventorySize = pPlayerInventory.size();

    for (int i = 0; i < m_playerInventorySize; ++i)
    {
        if (ItemsFactory::WeaponIDCheck(pPlayerInventory.at(i)->GetId()))
            m_pValidWeapons.push_back(pPlayerInventory.at(i));
    }
}

bool CycleWeapons::ProcessPlayerInput(char input)
{
    switch (input)
    {
    case 'w':
        Selection(&m_currentChosenIndex, 'w');
        break;
    case 's':
        Selection(&m_currentChosenIndex, 's');
        break;
    case 'a':
        m_pPlayer->SetCurrentWeapon(m_pValidWeapons.at(m_currentChosenIndex));
        std::cout << m_pValidWeapons.at(m_currentChosenIndex)->ItemName() << " equipped.\n";
        _getch();
        break;
    case 'q':
        return true;
    default:
        break;
    }

    return false;
}

void CycleWeapons::DisplayPlayerWeapons()
{
    for (int i = 0; i < m_verifiedWeaponary; ++i)
    {
        if (i == m_currentChosenIndex)
        {
            std::cout << "[" << m_cursor << "]" << " Gun Name: " << m_pValidWeapons.at(i)->ItemName() << "\n";
        }

        else
        {
            std::cout << "[" << m_marker << "]" << " Gun Name: " << m_pValidWeapons.at(i)->ItemName() << "\n";
        }
    }
}

bool CycleWeapons::CycleWeaponry(std::vector<class Items*> pPlayerInventory, Items &pPlayerCurrentWeapon)
{
    // Step 1. If the vector m_pValidWeapons isn't empty, clear it out.
    CheckWeaponSize();

    // Step 2. Gather all weapons in the players inventory to use.
    ProcessWeapons(pPlayerInventory);

    // Step 3. Save size of weapons.
    m_verifiedWeaponary = m_pValidWeapons.size();

    // Step 4. Begin loop.
    while (true)
    {
        system("cls");

        std::cout << "----------INVENTORY----------\n";

        DisplayPlayerWeapons();
        
        std::cout << "\n\n\nUse the [w] and [s] keys to cycle through inventory. Press [a] to select a weapon. Press [q] to exit inventory screen.\n";

        char input = _getch();

        if (ProcessPlayerInput(input))
            break;
    }

    return true;
}