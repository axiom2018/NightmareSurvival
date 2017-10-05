// Vendor.h
#include "Vendor.h"
#include "Player.h"
#include "WeaponsFactory.h"
#include "UpgradeFactory.h"
#include "Items.h"
#include "Pistol.h"
#include "World.h"
#include "Mediator.h"
#include <conio.h>
#include <string>


Vendor::Vendor(Mediator *pMediator) :
    m_displayShop(true),
    m_currentChosenIndex(0),
    m_cursor('S'),
    m_marker(' '),
    m_upgradeTracker(0),
    m_weaponTracker(0)
{
    // Step 1. Save mediator pointer for later use.
    m_pMediator = pMediator;
    // Step 2. Init weapons factory.
    m_pWF = new WeaponsFactory;
    // Step 3. Init upgrade factory.
    m_pUF = new UpgradeFactory;
    // Step 4. Set variables.
    m_max = 0;
    m_price = 225;
    // Step 5. Dynamically grab all upgrades and weapons. Allows us to add any upgrade/weapon, this will still work.
    GetAllUpgrades();
    GetAllWeapons();
}

void Vendor::DeleteItemPointer(Items *pItem)
{
    delete pItem;
    pItem = nullptr;
}

void Vendor::OpenVendorShop()
{
    OpenVendorsShop();
}

// Collects all upgrades from upgrade factory.
void Vendor::GetAllUpgrades()
{    
    m_max = 0;

    while (true)
    {
        m_pItem = m_pUF->GetItem(m_max);

        if (m_pItem)
        {
            m_pProducts.push_back(std::make_pair(m_pItem, k_upgradePrice));
            ++m_max;
            ++m_upgradeTracker;
            continue;
        }

        DeleteItemPointer(m_pItem);
        break;
    }
}

// Collects all weapons from weapon factory.
void Vendor::GetAllWeapons()
{
    m_max = 0;

    while (true)
    {
        m_pItem = m_pWF->GetItem(m_max);

        if (m_pItem)
        {
            m_pProducts.push_back(std::make_pair(m_pItem, m_price));
            m_price += m_price;
            ++m_max;
            ++m_weaponTracker;
            continue;
        }

        DeleteItemPointer(m_pItem);
        break;
    }
}

// Helps the player use the Weapon/Upgrade GUI with certain keys.
void Vendor::NormalCursorMovement(int *pIndex, char direction)
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
        std::cout << "Invalid direction!\n";
        break;
    }
}

// Move the cursor down. Has protection if player moves the cursor up despite it might being at the bottom.
void Vendor::MoveCursorDown(int *pIndex, char direction)
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

// Move the cursor up. Has protection if player moves the cursor up despite it might being at the top.
void Vendor::MoveCursorUp(int *pIndex, char direction)
{
    switch (direction)
    {
    case 'w':
        *pIndex = m_productSize - 1;
        break;
    case 's':
        *pIndex += 1;
        break;
    default:
        std::cout << "Invalid direction! [MoveCursorTop]";
        break;
    }
}

// Depending on the position of the cursor, we move up or down.
void Vendor::Selection(int *pIndex, char direction)
{
    if (*pIndex == 0)
    {
        MoveCursorUp(pIndex, direction);
        return;
    }

    else if (*pIndex == m_productSize - 1)
    {
        MoveCursorDown(pIndex, direction);
        return;
    }

    NormalCursorMovement(pIndex, direction);
}

bool Vendor::Transaction(int listedIndex)
{
    // Step 1. Get player money.
    int playersMoney = m_pMediator->GetPlayerMoney(this);

    // Step 2. Get value of product player wants to buy.
    int productPrice = m_pProducts.at(listedIndex).second;

    // Step 3. Check if they have enough to complete the transaction.
    if (playersMoney < productPrice)
        return false;

    // Step 4. If player has 100, product costs 10, simply subtract the amount of money the player has from the product price. The remaining value is the players change.
    int change = playersMoney - productPrice;
    m_pMediator->SetPlayerMoney(this, change);

    return true;
}

// Give item to player.
void Vendor::AddItem(int listedIndex)
{
    if (listedIndex <= m_upgradeTracker - 1) // Is it in the upgrade range? We added items that upgrade player stats into m_pProducts first.
    {
        m_pMediator->DeliverPlayerItem(this, m_pUF->GetItem(listedIndex));
    }

    else if (listedIndex > m_upgradeTracker - 1) // Is it in the weapons range? We added items that are weapons into the m_pProducts vector last.
    {
        int weaponsIndex = listedIndex - m_upgradeTracker;
        m_pMediator->DeliverPlayerItem(this, m_pWF->GetItem(weaponsIndex));
    }
}

// Allow player to purchase item if they have enough currency.
void Vendor::PurchaseItem()
{
    if (Transaction(m_currentChosenIndex))
    {
        // Player had enough money. Transaction went through.
        AddItem(m_currentChosenIndex);
        std::cout << "(Vendor says) Enjoy your new " << m_pProducts.at(m_currentChosenIndex).first->ItemName() << "\n";
        _getch();
        return;
    }

    // Player doesn't have enough money.
    std::cout << "(Vendor says) Apologies, you don't seem to have enough money.\n";
    _getch();
}

bool Vendor::ProcessPlayerInput(char input)
{
    // Step 1. Process given input.
    switch (input)
    {
    case 'w':
        Selection(&m_currentChosenIndex, 'w');
        break;
    case 's':
        Selection(&m_currentChosenIndex, 's');
        break;
    case 'a':
        PurchaseItem();
        break;
    case 'q':
        system("cls");
        return true; // Return true if player wants to exit vendor shop.
    default:
        std::cout << "Invalid key! [CycleWeapons.cpp]";
    }

    return false;
}

void Vendor::DisplayVendorControls()
{
    std::cout << "\n\nMoney you have: " << m_pMediator->GetPlayerMoney(this);
    std::cout << "\n\n\nUse the [w] and [s] keys to cycle through inventory.\n";
    std::cout << "Press [a] to select an item. Press[q] to exit inventory screen.\n\n";
}

void Vendor::DisplayVendorMessage()
{
    system("cls");
    std::cout << "----------VENDOR SHOP----------\n";
    std::cout << "(Vendor says) Hello there! What would you like to purchase?\n";
}

// Gather all products and display to the player.
void Vendor::DisplayPurchaseOptions()
{
    for (int i = 0; i < m_productSize; ++i)
    {
        if (i == m_currentChosenIndex)
        {
            std::cout << "[" << m_cursor << "]" << " Item Name: " << m_pProducts.at(i).first->ItemName() << " Price: " << m_pProducts.at(i).second << "\n";
        }

        else
        {
            std::cout << "[" << m_marker << "]" << " Item Name: " << m_pProducts.at(i).first->ItemName() << " Price: " << m_pProducts.at(i).second << "\n";
        }
    }
}

void Vendor::OpenVendorsShop()
{
    // Step 1. Get size of products to determine how many to display.
    m_productSize = m_pProducts.size();

    // Step 2. Begin while loop to open shop.
    while (true)
    {
        DisplayVendorMessage();

        DisplayPurchaseOptions();

        DisplayVendorControls();

        char input = _getch();

        if (ProcessPlayerInput(input))
            break;
    }
}

void Vendor::DeleteVendor()
{
    delete m_pWF;
    m_pWF = nullptr;
    delete m_pUF;
    m_pUF = nullptr;
    delete m_pItem;
    m_pItem = nullptr;

    for (std::vector<std::pair<class Items*, int>>::iterator it = m_pProducts.begin(); it != m_pProducts.end(); ++it)
    {
        delete (*it).first;
    }

    m_pProducts.clear();
}
