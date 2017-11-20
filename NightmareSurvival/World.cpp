// World.cpp
#include <conio.h>
#include "World.h"
#include "Player.h"
#include "Entities.h"
#include "Dots.h"
#include "Border.h"
#include "Enemies.h"
#include "EnemyManagement.h"
#include "ObjectPool.h" 
#include "WaveManager.h"
#include "VendorMediator.h"
#include "WalletMediator.h"
#include "BulletManager.h"
#include "Vendor.h"
#include "Definitions.h"

// Initialize singleton to nullptr.
World *World::m_pInstance = nullptr;

// Initialize world and other necessary variables.
World::World() :
    m_gameRunning(true)
{
    // Step 1. Init mediator for player and vendor.
    m_pVendorMediator = new VendorMediator;
    // Step 2. Init mediator for enemies and players wallet.
    m_pWalletMediator = new WalletMediator;
    // Step 3. Init player.
    m_pPlayer = new Player;
    // Step 4. Get Players wallet and register it in the WalletMediator.
    m_pWalletMediator->RegisterParticipant(m_pPlayer->GetWallet());
    // Step 5. Init vendor.
    m_pVendor = new Vendor(m_pVendorMediator);
    // Step 6. Register player with first mediator.
    m_pVendorMediator->RegisterParticipant(m_pPlayer);
    // Step 7. Register Vendor with first mediator.
    m_pVendorMediator->RegisterParticipant(m_pVendor);
    // Step 8. Init enemy management pointer.
    m_pEnemyManagement = new EnemyManagement;
    // Step 9. Init bullet manager.
    m_pBulletManager = new BulletManager;
}

// Singleton management function.
World *World::Instance()
{
    if (m_pInstance == 0)
    {
        m_pInstance = new World;
    }

    return m_pInstance;
}

// Create game board and align outer lines of it.
void World::CreateWorld()
{
    // Step 1. Assign memory to pointer.
    m_ppSpace = new Entities*[COLUMNS * ROWS];

    // Step 2. Set to nullptr.
    for (int i = 0; i < COLUMNS * ROWS; ++i)
    {
        m_ppSpace[i] = nullptr;
    }

    // Step 3. Set the top border.
    for (int x = 0; x < ROWS; ++x)
    {
        for (int y = 0; y < COLUMNS; ++y)
        {
            int index = (x * COLUMNS) + y;
            if (index < COLUMNS)
            {
                m_ppSpace[index] = new Border;
            }
        }
    }

    // Step 4. Set bottom border.
    int max = COLUMNS * ROWS;
    int position = max - (COLUMNS - 1);
    for (int i = position; i < max; ++i)
    {
        m_ppSpace[position] = new Border;
        ++position;
    }

    // Step 5. Set the left border.
    for (int i = COLUMNS; i < COLUMNS * ROWS; i += COLUMNS)
    {
        m_ppSpace[i] = new Border;
    }

    // Step 6. Set the right border.
    for (int i = 2; i < ROWS; ++i)
    {
        int pos = COLUMNS * i - 1;
        m_ppSpace[pos] = new Border;
    }

    // Step 7. Work on inner layer of game board.
    for (int x = 0; x < ROWS; ++x)
    {
        for (int y = 0; y < COLUMNS; ++y)
        {
            int index = (x * COLUMNS) + y;
            if (m_ppSpace[index] == nullptr)
            {
                m_ppSpace[index] = new Dots;
            }
        }
    }

    // Step 8. Generate the waves of enemies.
    m_pEnemyManagement->GenerateEnemies();
}

// Controls the game running and referenced in Main.cpp.
bool World::CheckIsGameRunning() const
{
    return m_gameRunning;
}

// Referenced in EnemyManagement.cpp.
WalletMediator * World::GetWalletMediator() const
{
    return m_pWalletMediator;
}

// Referenced in BulletManager.cpp and ManageEnemyPosition.cpp.
EnemyManagement * World::GetEnemyManager() const
{
    return m_pEnemyManagement;
}

// Referenced in WeaponManager.cpp.
BulletManager * World::GetBulletManager() const
{
    return m_pBulletManager;
}

// Referenced in ArmorStrategy.cpp, BulletManager.cpp, CalculateMove.cpp, and FirstAidStrategy.cpp.
Player * World::GetPlayer() const
{
    return m_pPlayer;
}

// CalculateMove.cpp calls CheckBorder as a movement test for enemies.
bool World::CheckBorder(int index) const
{
    if (m_ppSpace[index]->GetChar() == '#')
        return true;

    return false;
}

bool World::MoveToNextLevel()
{
    // Step 1. Check if enemy vector is empty, if so, all enemies are dead. If not, exit function early.
    if (!m_pEnemyManagement->EnemiesDead())
        return false;

    // Step 2. Check if Wave 5 is the wave we just cleared, if so, terminate the game.
    if (m_pEnemyManagement->GetWaveManager()->NextWave())
    {
        std::cout << "You survived! Congratulations!\n";
        return true;
    }

    // Step 3. Deliver message to player.
    std::cout << "Wave " << m_pEnemyManagement->GetWaveManager()->GetCurrentWave() << " cleared!\n\n\n";
    std::cout << "Press <enter> to shop at Vendor for Weapons & Upgrades!\n";
    _getch();

    // Step 4. Open vendor.
    m_pVendorMediator->OpenVendorShop(m_pPlayer);

    // Step 5. Generate enemies if Step 2 didn't terminate the game. 
    m_pEnemyManagement->GenerateEnemies();

    // Step 6. Scan game board for bullets. If there are any, place them back into the pool.
    m_pBulletManager->ReturnAllBulletsOnGameBoard();

    // Step 7. Reset the players position.
    m_pPlayer->ResetPlayerPosition();

    return false;
}

bool World::DrawPlayer(int x, int y)
{
    if (x == m_pPlayer->GetY()
        && y == m_pPlayer->GetX())
    {
        m_pPlayer->DrawPlayer();
        return true;
    }

    return false;
}

// Draw world.
void World::UpdateWorld()
{
    for (int x = 0; x < ROWS; ++x)
    {
        for (int y = 0; y < COLUMNS; ++y)
        {
            if (DrawPlayer(x, y))
                continue;

            if (m_pBulletManager->DrawBullets(x, y))
                continue;

            if (m_pEnemyManagement->DrawEnemy(x, y))
                continue;

            int index = (x * COLUMNS) + y;
            m_ppSpace[index]->Draw();
        }

        std::cout << "\n";
    }
}

void World::Update()
{
    // Step 1. Check if current enemies are all dead. 
    if (MoveToNextLevel())
    {
        m_gameRunning = false;
        return;
    }

    // Step 2. Update enemy movements.
    m_pEnemyManagement->UpdateEnemyMovement();

    // Step 3. Re-draw world.
    UpdateWorld(); 

    // Step 4. Update any possible bullets on screen.
    m_pBulletManager->UpdateBullets();

    // Step 5. Draw player information.
    m_pPlayer->DrawControls();
    m_pPlayer->DrawStats();

    // Step 6. Get player input.
    if (!m_pPlayer->UpdatePlayer())
    {
        m_gameRunning = false;
        return;
    }

    // Step 7. Wipe screen with system call.
    system("cls");
}

void World::TerminateGame()
{
    m_gameRunning = false;
}

void World::DeleteWorld()
{
    ObjectPool::GetInstance()->DeletePool();

    delete m_pEnemyManagement;
    m_pEnemyManagement = nullptr;
    
    delete m_pBulletManager;
    m_pBulletManager = nullptr;

    for (int i = 0; i < COLUMNS * ROWS; ++i)
    {
        delete m_ppSpace[i];
    }

    delete m_pPlayer;
    m_pPlayer = nullptr;

    m_pVendor->DeleteVendor();
    delete m_pVendor;
    m_pVendor = nullptr;

    delete m_pVendorMediator;
    m_pVendorMediator = nullptr;

    delete m_pWalletMediator;
    m_pWalletMediator = nullptr;

    delete m_pVendor;
    m_pVendor = nullptr;

    delete[] m_ppSpace;
    m_ppSpace = nullptr;

    delete m_pInstance;
    m_pInstance = nullptr;
}