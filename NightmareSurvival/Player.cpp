// Player.cpp
#include "Player.h"
#include "PlayerGameControls.h"
#include "World.h"
#include "HealthManager.h"
#include "Entities.h"
#include "Border.h"
#include "Items.h"
#include <iostream>
#include "CycleWeapons.h"
#include "Vendor.h"
#include "BorderManagement.h"
#include "Wallet.h"
#include "InventoryManager.h"
#include "ArmorManager.h"
#include "Definitions.h"
#include <conio.h>
#include <string>

// Set up player.
Player::Player() :
    m_player('^'),
    m_ammunition(0),
    m_x(0),
    m_y(0),
    m_direction(Directions::North)
{
    // Step 1. Set player's position.
    m_x = COLUMNS / 2;
    m_y = ROWS / 2;

    // Step 2. Init inventory manager.
    m_pInventoryManager = new InventoryManager;

    // Step 3. Init border manager.
    m_pBorderManagement = new BorderManagement(&m_x, &m_y);

    // Step 4. Init wallet.
    m_pWallet = new Wallet;

    // Step 5. Init health management.
    m_pHealthManager = new HealthManager(PLAYER_HEALTH);

    // Step 6. Init armor management.
    m_pArmorManager = new ArmorManager;
}

// Depending on the key pressed, change direction of player.
void Player::AlterDirection(char key)
{
    switch (key)
    {
    case m_up:
        m_direction = Directions::North;
        m_player = '^';
        break;
    case m_left:
        m_direction = Directions::West;
        m_player = '<';
        break;
    case m_down:
        m_direction = Directions::South;
        m_player = 'v';
        break;
    case m_right:
        m_direction = Directions::East;
        m_player = '>';
        break;
    default:
        break;
    }
}

// Referenced in World.cpp.
void Player::DrawPlayer() const
{
    std::cout << m_player;
}

// Referenced in World.cpp.
bool Player::UpdatePlayer()
{
    char input = _getch();

    switch (input)
    {
    case m_up:
        if(!m_pBorderManagement->CheckAreaForBorders(input))
            m_y -= 1;
        break;
    case m_left:
        if (!m_pBorderManagement->CheckAreaForBorders(input))
            m_x -= 1;
        break;
    case m_down:
        if (!m_pBorderManagement->CheckAreaForBorders(input))
            m_y += 1;
        break;
    case m_right:
        if (!m_pBorderManagement->CheckAreaForBorders(input))
            m_x += 1;
        break;
    case m_quit:
        m_pInventoryManager->ShootWeapon();
        break;
    case m_reload:
        m_pInventoryManager->UseUpgrade(AMMUNITION_ID);
        break;
    case m_openInventory:
        m_pInventoryManager->OpenInventory();
        break;
    case m_useFirstAid:
        m_pInventoryManager->UseUpgrade(FIRSTAID_ID);
        break;
    case m_useUpgrade:
        m_pInventoryManager->UseUpgrade(ARMOR_ID);
        break;
    case m_exitGame: // Press 'e' any time during the game to exit properly without leaking memory. 
        return false;
    default:
        break;
    }

    AlterDirection(input);

    return true;
}

// Referenced in World.cpp.
void Player::DrawControls() const
{
    std::cout << (char)m_quit << "=Shoot " << (char)m_reload << "=Reload " << (char)m_openInventory << "=Inventory " << (char)m_useFirstAid << "=FirstAid ";
    std::cout << (char)m_useUpgrade << "=UseArmor\n";
    std::cout << "Press " << (char)m_exitGame << " to quit.\n";
}

// Referenced in World.cpp.
void Player::DrawStats() const
{
    std::cout << "Health: " << m_pHealthManager->GetHealth() << " Armor: " << m_pArmorManager->GetArmor() << " Money: " << m_pWallet->GetFunds() << "\n";
    std::cout << "Equipped Gun: " << m_pInventoryManager->GetWeaponName() << "   Ammo: " << m_pInventoryManager->GetWeaponAmmunition();
}

// Referenced in World.cpp.
WalletManagementParticipants * Player::GetWallet() const
{
    return m_pWallet;
}

// Referenced in FirstAidStrategy.cpp.
HealthManager * Player::GetHealthManager() const
{
    return m_pHealthManager;
}

// Referenced in ArmorStrategy.cpp.
ArmorManager * Player::GetArmorManager() const
{
    return m_pArmorManager;
}

// Referenced in World.cpp.
int Player::GetX() const
{
    return m_x;
}

// Referenced in World.cpp.
int Player::GetY() const
{
    return m_y;
}

// Referenced in BulletManager.
Directions Player::GetDirection() const
{
    return m_direction;
}

// Manage player damage.
void Player::Damage(int damage)
{
    // Step 1. See if player has armor that can absorb damage first.
    if (m_pArmorManager->DamageArmor(damage))
        return;

    // Step 2. Damage health if no armor was available in Step 1.
    if (m_pHealthManager->DamageHealth(damage))
        World::Instance()->TerminateGame();
}

// Referenced in World.cpp.
void Player::ResetPlayerPosition()
{
    m_x = COLUMNS / 2;
    m_y = ROWS / 2;
}

// Overriden function found in Participants.h.
int Player::GetPlayerMoney() const
{
    return m_pWallet->GetFunds();
}

// Overriden function found in Participants.h.
void Player::SetPlayerMoney(int value)
{
    m_pWallet->ReceiveChange(value);
}

// Overriden function found in Participants.h.
void Player::DeliverPlayerItem(Items * pItem)
{
    m_pInventoryManager->AddToInventory(pItem);
}

Player::~Player()
{
    delete m_pInventoryManager;
    m_pInventoryManager = nullptr;

    delete m_pBorderManagement;
    m_pBorderManagement = nullptr;

    delete m_pWallet;
    m_pWallet = nullptr;

    delete m_pHealthManager;
    m_pHealthManager = nullptr;

    delete m_pArmorManager;
    m_pArmorManager = nullptr;
}