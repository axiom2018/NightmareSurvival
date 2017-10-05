// Player.cpp
#include "Player.h"
#include "World.h"
#include "Entities.h"
#include "Border.h"
#include "Items.h"
#include "BulletAlgorithm.h"
#include <iostream>
#include "WeaponsFactory.h"
#include "CycleWeapons.h"
#include "Vendor.h"
// #include "Mediator.h"
#include "BorderManagement.h"
#include "Wallet.h"
#include <conio.h>
#include <string>

// Why does player need to know about mediator anyway?
// Player::Player(int worldWidth, int worldHeight) :
// Player::Player(int worldWidth, int worldHeight, Mediator *pMediator) :
Player::Player(int worldWidth, int worldHeight) :
    m_directions(Directions::North),
    m_player('^'),
    m_health(80),
    m_armor(0),
    m_money(0),
    m_coolDown(2),
    m_saveWorldWidth(0),
    m_saveWorldHeight(0)
{
    m_saveWorldWidth = worldWidth;
    m_saveWorldHeight = worldHeight;

    m_x = m_saveWorldWidth / 2;
    m_y = m_saveWorldHeight / 2;

    m_pCycleInventory = new CycleWeapons(this);
    m_pWF = new WeaponsFactory;
    // m_pMediator = pMediator; 
    m_pBorderManagement = new BorderManagement(&m_x, &m_y, m_saveWorldWidth, m_saveWorldHeight);
    m_pWallet = new Wallet;

    m_pInventory.push_back(m_pWF->GetItem(0)); // Get Pistol.
    m_pCurrentWeapon = m_pInventory.at(0); // Set current weapon to the Pistol.
    m_pBulletControl = new BulletAlgorithm(worldWidth, worldHeight);
}

void Player::CycleWeaponInventory()
{
    // Step 1. Get inventory size for loops and set variable to keep track of weapons in inventory.
    int playerInventorySize = m_pInventory.size();
    int totalWeapons = 0;

    // Step 2. Get the ID's of each entity in inventory and test if they are weapons and not items.
    for (int i = 0; i < playerInventorySize; ++i)
    {
        if (ItemsFactory::WeaponIDCheck(m_pInventory.at(i)->GetId()))
            ++totalWeapons;
    }

    // Step 3. If player has more than 1 weapon, open inventory.
    if (totalWeapons > 1)
    {
        m_pCycleInventory->CycleWeaponry(m_pInventory, *m_pCurrentWeapon);
        return;
    }   

    // (Optional Step) If Step 3 is false, alert the player to get more weapons in their arsenal.
    std::cout << " You only have 1 weapon! Get more weapons!\n";
}

bool Player::CheckAreaForBorders(char key)
{
    switch (key)
    {
    case 'w':
        if (m_pBorderManagement->NorthBorderCheck())
            return true;
        break;
    case 'a':
        if (m_pBorderManagement->WestBorderCheck())
            return true;
        break;
    case 's':
        if (m_pBorderManagement->SouthBorderCheck())
            return true;
        break;
    case 'd':
        if (m_pBorderManagement->EastBorderCheck())
            return true;
        break;
    default:
        break;
    }

    return false;
}

bool Player::UpdatePlayer()
{
    char input = _getch();

    switch (input)
    {
    case 'w':
        if (!CheckAreaForBorders(input))
            m_y -= 1;
        break;
    case 'a':
        if (!CheckAreaForBorders(input))
            m_x -= 1;
        break;
    case 's':
        if (!CheckAreaForBorders(input))
            m_y += 1;
        break;
    case 'd':
        if (!CheckAreaForBorders(input))
            m_x += 1;
        break;
    case 'q':
        Shoot();
        break;
    case 'r':
        Reload();
        break;
    case 'i':
        CycleWeaponInventory();
        break;
    case 'f':
        UseFirstAid();
        break;
    case 'g':
        UseArmor();
        break;
    case 'e': // Press 'e' any time during the game to exit PROPERLY without leaking memory. I implemented this when I started building to make sure memory was cleaned properly.
        return false;
    default:
        break;
    }

    AlterDirection(input);

    return true;
}

void Player::DrawControls() const
{
    std::cout << "(q)Shoot " << "(r)Reload " << "(i)Inventory " << "(f)First Aid " << "(G)Use Armor\n";
    std::cout << "Press (e) to quit.\n";
}

void Player::DrawStats() const
{
    std::cout << "Health: " << m_health << " Armor: " << m_armor << " Money: " << m_money << "\n";
    std::cout << "Equipped Gun: " << m_pCurrentWeapon->ItemName() << "   Ammo: " << m_pCurrentWeapon->GetAmmo();
}

bool Player::WeaponCoolDown()
{
    if (m_coolDown == 0)
        return true; 

    --m_coolDown;

    return false;
}

bool Player::WeaponAmmunitionCheck(int weaponAmmo) const
{
    if (weaponAmmo == 0)
    {
        std::cout << " Reload immediately!\n";
        return true;
    }

    return false;
}

void Player::Shoot()
{
    // Step 1. If cooldown is not at 0, do not continue with function.
    if (!WeaponCoolDown())
        return;

    // Step 2. If weapon is out of ammunition, do not continue with function.
    if (WeaponAmmunitionCheck(m_pCurrentWeapon->GetAmmo()))
        return;

    // Step 3. Carry out shooting commands.
    m_pBulletControl->BulletManager(m_pCurrentWeapon->GetId());

    // Step 4. Decrease ammo and reset cooldown.
    m_pCurrentWeapon->DecreaseAmmo();
    m_coolDown = 2;
}

int Player::GetBulletsSize() const
{
    return m_pBulletControl->GetBulletSize();
}

bool Player::ArmorDamage(int damage)
{
    // Step 1. If armor was 0 to begin with, exit function
    if (m_armor <= 0)
        return false;

    // Step 2. If we haven't returned in step 1, apply armor damage.
    m_armor -= damage;
    return true;
}

void Player::Damage(int damage)
{
    // Step 1. Check if we have armor that can absorb initial damage first.
    if (ArmorDamage(damage))
        return;

    // Step 2. Assign damage to health.
    int remainder = m_health - damage;
    if (remainder <= 0)
    {
        m_health = 0;
        World::Instance()->TerminateGame();
        return;
    }
       
    m_health -= damage;
}

bool Player::DrawBullets(int x, int y)
{
    if (m_pBulletControl->DrawBullets(x, y))
        return true;
    
    return false;
}

void Player::EnemyCollision()
{
    m_pBulletControl->EnemyCollision();
}

void Player::UpdateBullets()
{
    m_pBulletControl->UpdateBullets();
}

bool Player::ApplyUpgrade(int typeOfUpgrade, int index)
{
    switch (typeOfUpgrade)
    {
    case 3: // Firstaid.
        m_health += m_pInventory.at(index)->GetUpgradeAmount();
        return true;
    case 4: // Armor.
        m_armor += m_pInventory.at(index)->GetUpgradeAmount();
        return true;
    case 5: // Ammo.
        m_pCurrentWeapon->Reload(m_pInventory.at(index)->GetUpgradeAmount());
        return true;
    default:
        break;
    }

    return false;
}

bool Player::UseUpgrade(int typeOfUpgrade)
{
    // Step 1. Get inventory size.
    m_playerInventorySize = m_pInventory.size();

    // Step 2. Cycle through entire inventory and check if player HAS the upgrade they request.
    for (int i = 0; i < m_playerInventorySize; ++i)
    {
        if (m_pInventory.at(i)->GetId() == typeOfUpgrade)
        {
            // Step 3. If step 2 passed, apply the the upgrade. In not, go to next item in inventory.
            if (!ApplyUpgrade(typeOfUpgrade, i))
                continue;

            // Step 4. Delete item from vector ensuring no memory leaks.
            Items *pItem = m_pInventory.at(i);
            delete pItem;
            pItem = nullptr;

            // Step 5. Erase item from player inventory.
            m_pInventory.erase(m_pInventory.begin() + i);
            return true;
        }
    }

    return false;
}

void Player::UseArmor()
{
    if (!UseUpgrade(4))
        std::cout << "\nNo armor in inventory!\n";
}

void Player::UseFirstAid()
{
    if (!UseUpgrade(3))
        std::cout << "\nNo health in inventory!\n";
}

void Player::Reload()
{
    if (!UseUpgrade(5))
        std::cout << "\nNo ammo in inventory!\n";
}

void Player::AlterDirection(char key)
{
    switch (key)
    {
    case 'w':
        m_directions = Directions::North;
        m_player = '^';
        break;
    case 'a':
        m_directions = Directions::West;
        m_player = '<';
        break;
    case 's':
        m_directions = Directions::South;
        m_player = 'v';
        break;
    case 'd':
        m_directions = Directions::East;
        m_player = '>';
        break;
    default:
        break;
    }
}

Player::~Player()
{
    for (std::vector<Items*>::iterator it = m_pInventory.begin(); it != m_pInventory.end(); ++it)
    {
        delete (*it);
    }
    m_pInventory.clear();

    delete m_pCycleInventory;
    m_pCycleInventory = nullptr;

    delete m_pWF;
    m_pWF = nullptr;

    delete m_pBulletControl;
    m_pBulletControl = nullptr;

    delete m_pBorderManagement;
    m_pBorderManagement = nullptr;

    delete m_pWallet;
    m_pWallet = nullptr;
}