// UpgradeManager.cpp
#include "UpgradeManager.h"
#include "Items.h"
#include "ArmorStrategy.h"
#include "AmmoStrategy.h"
#include "FirstAidStrategy.h"
#include "Definitions.h"

UpgradeManager::UpgradeManager() :
    m_pUpgradeStrategy(nullptr),
    m_index(-1)
{
    
}

bool UpgradeManager::FindUpgrade(std::vector<class Items*> * pInventory, int itemID)
{
    // Step 1. Get inventory size.
    int size = pInventory->size();

    // Step 2. Loop through inventory and return true if item was found.
    for (int i = 0; i < size; ++i)
    {
        if (pInventory->at(i)->GetId() == itemID)
        {
            m_index = i;

            m_pItem = pInventory->at(i);

            pInventory->erase(pInventory->begin() + i);

            return true;
        }
    }

    // (Optional Step) Return false if item was not found.
    return false;
}


void UpgradeManager::UseUpgrade(int itemID, std::vector<class Items*> * pInventory, class WeaponManager *pWeaponManager)
{
    // Step 1. Find the upgrade in the inventory.
    if (!FindUpgrade(pInventory, itemID))
        return;
    
    // Step 2. Delete the old strategy.
    if (m_pUpgradeStrategy != nullptr)
    {
        delete m_pUpgradeStrategy;
        m_pUpgradeStrategy = nullptr;
    }

    // Step 3. Select strategy.
    switch (itemID)
    {
    case FIRSTAID_ID:
        m_pUpgradeStrategy = new FirstAidStrategy;
        break;
    case AMMUNITION_ID:
        m_pUpgradeStrategy = new AmmoStrategy;
        break;
    case ARMOR_ID:
        m_pUpgradeStrategy = new ArmorStrategy;
        break;
    default:
        break;
    }

    // Step 4. Apply upgrade changes.
    m_pUpgradeStrategy->Use(m_pItem, pWeaponManager);
}

UpgradeManager::~UpgradeManager()
{
    delete m_pUpgradeStrategy;
    m_pUpgradeStrategy = nullptr;
}
