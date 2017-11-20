// CycleWeapons.cpp
#include "CycleWeapons.h"
#include "ItemsFactory.h"
#include "Player.h"
#include "WeaponManager.h"
#include "CursorManager.h"
#include "PlayerGameControls.h"
#include <iostream>
#include <string>
#include <conio.h>

CycleWeapons::CycleWeapons(class WeaponManager *pWeaponManager) :
    m_cursor('S'),
    m_marker(' '),
    m_currentChosenIndex(0)
{
    // Step 1. Set weapon manager.
    m_pWeaponManager = pWeaponManager;

    // Step 2. Init Cursor Manager.
    m_pCursorManager = new CursorManager;
}

void CycleWeapons::SetWeapon()
{
    // Step 1. Check to see if weapon selected in WeaponryGUI is already the weapon selected.
    if (m_pWeaponManager->GetCurrentWeapon() == m_pValidWeapons.at(m_pCursorManager->GetChosenIndex()))
    {
        std::cout << "This weapon is already equipped!\n";
        return;
    }

    // Step 2. If Step 1 didn't exit the function early, the selected weapon is NOT already equipped. Equip it.
    m_pWeaponManager->SetWeapon(m_pValidWeapons.at(m_pCursorManager->GetChosenIndex()));

    // Step 3. Display message to player about selected weapon for confirmation.
    std::cout << m_pValidWeapons.at(m_pCursorManager->GetChosenIndex())->ItemName() << " equipped.\n";
}

// Clear out weapons if not empty inside the WeaponryGUI() function.
void CycleWeapons::CheckWeaponSize()
{
    if (m_pValidWeapons.empty())
        return;

    m_pValidWeapons.clear();
}

// Takes the whole inventory and weeds out the weapons, from the upgrades.
void CycleWeapons::ProcessWeapons(std::vector<class Items*> pInventory)
{
    m_playerInventorySize = pInventory.size();

    for (int i = 0; i < m_playerInventorySize; ++i)
    {
        if (ItemsFactory::WeaponIDCheck(pInventory.at(i)->GetId()))
            m_pValidWeapons.push_back(pInventory.at(i));
    }
}

// Show all weapons in a GUI.
void CycleWeapons::DisplayWeapons()
{
    for (int i = 0; i < m_verifiedWeaponary; ++i)
    {
        if (i == m_pCursorManager->GetChosenIndex())
        {
            std::cout << "[" << m_pCursorManager->GetSymbol(i) << "]" << " Gun Name: " << m_pValidWeapons.at(i)->ItemName() << "\n";
        }

        else
        {
            std::cout << "[" << m_pCursorManager->GetSymbol(i) << "]" << " Gun Name: " << m_pValidWeapons.at(i)->ItemName() << "\n";
        }
    }
}

void CycleWeapons::WeaponryGUI(std::vector<class Items*> pInventory, Items &pPlayerCurrentWeapon)
{
    // Step 1. If the vector m_pValidWeapons isn't empty, clear it out.
    CheckWeaponSize();

    // Step 2. Gather all weapons in the players inventory to use.
    ProcessWeapons(pInventory);

    // Step 3. Save size of weapons.
    m_verifiedWeaponary = m_pValidWeapons.size(); //Pass to cursor manager

    // Step 4. Begin loop.
    while (true)
    {
        system("cls");

        std::cout << "----------INVENTORY----------\n";

        DisplayWeapons();
        
        std::cout << "\n\n\nUse the " << (char)m_up << " and " << (char)m_down << " keys to cycle through inventory. ";
        std::cout << "Press " << (char)m_left << " to select a weapon. Press " << (char)m_quit << " to exit inventory screen.\n";

        char input = _getch();

        // Step 5. Get input.
        int result = m_pCursorManager->ProcessPlayerInput(input, m_verifiedWeaponary);

        // Step 6. Process that input.
        switch (result)
        {
        case 0:
            system("cls");
            return;
        case 1:
            SetWeapon();
            _getch();
            break;
        case -1:
            break;
        default:
            break;
        }
    }
}

CycleWeapons::~CycleWeapons()
{
    delete m_pCursorManager;
    m_pCursorManager = nullptr;
}
