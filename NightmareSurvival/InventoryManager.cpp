// InventoryManager.cpp
#include "InventoryManager.h"
#include "WeaponsFactory.h"
#include "CycleWeapons.h"
#include "ItemsFactory.h"
#include "CurrentWeaponManager.h"

// Set up variables.
InventoryManager::InventoryManager()
{
    // Step 1. Init weapons factory.
    m_pWF = new WeaponsFactory;

    // Step 2. Get default starting weapon for player from weapons factory.
    m_pInventory.push_back(m_pWF->GetItem(0)); 

    // Step 3. Init CycleWeapons interface.
    m_pCycleInventory = new CycleWeapons(this);

    // Step 4. Init CurrentWeaponManager.
    m_pCurrentWeaponManager = new CurrentWeaponManager;

    // Step 5. Assign current weapon to CurrentWeaponManager.
    m_pCurrentWeaponManager->SetWeapon(m_pInventory.at(0));
}

int InventoryManager::GetInventorySize() const
{
    return m_pInventory.size();
}

// Referenced in Player.cpp.
std::string InventoryManager::GetWeaponName() const
{
    return m_pCurrentWeapon->ItemName();
}

// Referenced in Player.cpp.
int InventoryManager::GetWeaponAmmunition() const
{
    return m_pCurrentWeapon->GetAmmo();
}

void InventoryManager::AddToInventory(Items * pItem)
{
    m_pInventory.push_back(pItem);
}

// Referenced in Player.cpp.
void InventoryManager::OpenInventory()
{
    // Step 1. Save inventory size.
    int inventorySize = m_pInventory.size();

    // Step 2. Save amount of total weapons.
    int maxWeapons = 0;

    // Step 3. Get ID's of each entity in inventory and see if they are weapons and not upgrades.
    for (int i = 0; i < inventorySize; ++i)
    {
        if (ItemsFactory::WeaponIDCheck(m_pInventory.at(i)->GetId()))
            ++maxWeapons;
    }

    // Step 4. If player has more than 1 weapon, proceed with opening inventory.
    if (maxWeapons > 1)
    {
        m_pCycleInventory->WeaponryGUI(m_pInventory, *m_pCurrentWeapon);
        return;
    }

    // (Optional Step) If Step 3 is false, alert the player to get more weapons in their arsenal.
    std::cout << " You only have 1 weapon! Get more weapons!\n";
}

void InventoryManager::SetPlayerCurrentWeapon(Items * pWeapon)
{
    m_pCurrentWeapon = pWeapon;
}

void InventoryManager::ShootWeapon()
{
    m_pCurrentWeaponManager->ShootWeapon();
}

InventoryManager::~InventoryManager()
{
    for (std::vector<Items*>::iterator it = m_pInventory.begin(); it != m_pInventory.end(); ++it)
    {
        delete (*it);
    }

    m_pInventory.clear();

    delete m_pWF;
    m_pWF = nullptr;

    delete m_pCycleInventory; 
    m_pCycleInventory = nullptr;

    delete m_pCurrentWeaponManager;
    m_pCurrentWeaponManager = nullptr;
}
