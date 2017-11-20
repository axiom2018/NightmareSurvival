// Vendor.h
#include "Vendor.h"
#include "Player.h"
#include "WeaponsFactory.h"
#include "UpgradeFactory.h"
#include "Items.h"
#include "Pistol.h"
#include "World.h"
#include "VendorMediator.h"
#include "CursorManager.h"
#include "CursorGUIControls.h"
#include "Definitions.h"
#include <conio.h>
#include <string>


Vendor::Vendor(VendorMediator *pMediator) :
    m_displayShop(true),
    m_upgradeTracker(0),
    m_weaponTracker(0)
{
    // Step 1. Save mediator pointer for later use.
    m_pMediator = pMediator;
    // Step 2. Init weapons factory.
    m_pWF = new WeaponsFactory;
    // Step 3. Init upgrade factory.
    m_pUF = new UpgradeFactory;
    // Step 3. Init cursor manager.
    m_pCursorManager = new CursorManager;
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

// Collects all upgrades from upgrade factory.
void Vendor::GetAllUpgrades()
{    
    m_max = 0;

    while (true)
    {
        m_pItem = m_pUF->GetItem(m_max);

        if (m_pItem)
        {
            m_pProducts.push_back(std::make_pair(m_pItem, UNIVERSAL_UPGRADE_PRICE));
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
    // Step 1. Get index.
    int index = m_pCursorManager->GetChosenIndex();

    // Step 2. Proceed with transaction.
    if (Transaction(index))
    {
        // Step 3. Player had enough money. Finish transaction.
        AddItem(index);
        std::cout << "(Vendor says) Enjoy your new " << m_pProducts.at(index).first->ItemName() << "\n";
        _getch();
        system("cls");
        return;
    }

    // (Optional Step) Player doesn't have enough money.
    std::cout << "(Vendor says) Apologies, you don't seem to have enough money.\n";
    _getch();
}

void Vendor::DisplayVendorControls()
{
    std::cout << "\n\nMoney you have: " << m_pMediator->GetPlayerMoney(this);
    std::cout << "\n\n\nUse the " << (char)m_up << " and " << (char)m_down << " keys to cycle through inventory.\n";
    std::cout << "Press " << (char)m_select << " to select an item. Press " << (char)m_quit << " to exit inventory screen.\n\n";
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
        if (i == m_pCursorManager->GetChosenIndex())
        {
            std::cout << "[" << m_pCursorManager->GetSymbol(i) << "]" << " Item Name: " << m_pProducts.at(i).first->ItemName() << " Price: " << 
                m_pProducts.at(i).second << "\n";
        }

        else
        {
            std::cout << "[" << m_pCursorManager->GetSymbol(i) << "]" << " Item Name: " << m_pProducts.at(i).first->ItemName() << " Price: " << 
                m_pProducts.at(i).second << "\n";
        }
    }
}

// Allow player to browse Vendor shop.
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

        int result = m_pCursorManager->ProcessPlayerInput(input, m_productSize);

        switch (result)
        {
        case 0:
            system("cls");
            return;
        case 1:
            PurchaseItem();
            break;
        case -1:
            break;
        default:
            break;
        }
    }
}

// Override virtual function.
void Vendor::OpenVendorShop()
{
    OpenVendorsShop();
}

void Vendor::DeleteVendor()
{
    delete m_pWF;
    m_pWF = nullptr;
    delete m_pUF;
    m_pUF = nullptr;
    delete m_pItem;
    m_pItem = nullptr;
    delete m_pCursorManager;
    m_pCursorManager = nullptr;

    for (std::vector<std::pair<class Items*, int>>::iterator it = m_pProducts.begin(); it != m_pProducts.end(); ++it)
    {
        delete (*it).first;
    }

    m_pProducts.clear();
}
