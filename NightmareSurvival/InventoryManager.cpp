// InventoryManager.cpp
#include "InventoryManager.h"
#include "WeaponManager.h"
#include "UpgradeManager.h"
#include "Items.h"

// Set up variables.
InventoryManager::InventoryManager()
{
    // Step 1. Init WeaponManager.
    m_pWeaponManager = new WeaponManager;

    // Step 2. Init UpgradeManager.
    m_pUpgradeManager = new UpgradeManager;

    // Step 3. Get default starting weapon for player from weapons factory.
    m_pInventory.push_back(m_pWeaponManager->GetCurrentWeapon());
}

// Referenced in UpgradeManager.cpp. Needed in order to get access to ammunition getter/setter.
WeaponManager * InventoryManager::GetWeaponManager() const
{
    return m_pWeaponManager;
}

// Referenced in Player.cpp. Delegated to weapon manager.
std::string InventoryManager::GetWeaponName() const
{
    return m_pWeaponManager->WeaponName();
}

// Referenced in Player.cpp. Delegated to weapon manager.
int InventoryManager::GetWeaponAmmunition() const
{
    return m_pWeaponManager->GetWeaponAmmunition();
}

void InventoryManager::AddToInventory(Items * pItem)
{
    m_pInventory.push_back(pItem);
}

// Referenced in Player.cpp. Delegated to weapon manager.
void InventoryManager::OpenInventory()
{
    m_pWeaponManager->OpenWeaponInventory(m_pInventory);
}

// Delegated to weapon manager.
void InventoryManager::SetPlayerCurrentWeapon(Items * pWeapon)
{
    m_pWeaponManager->SetWeapon(pWeapon);
}

// Referenced in Player.cpp. Delegated to weapon manager.
void InventoryManager::ShootWeapon()
{
    m_pWeaponManager->ShootWeapon();
}

void InventoryManager::UseUpgrade(int itemID)
{
    m_pUpgradeManager->UseUpgrade(itemID, &m_pInventory, m_pWeaponManager);
}

InventoryManager::~InventoryManager()
{
    for (std::vector<Items*>::iterator it = m_pInventory.begin(); it != m_pInventory.end(); ++it)
    {
        delete (*it);
    }

    m_pInventory.clear();

    delete m_pWeaponManager;
    m_pWeaponManager = nullptr;

    delete m_pUpgradeManager;
    m_pUpgradeManager = nullptr;
}
