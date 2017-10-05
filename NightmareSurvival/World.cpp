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
#include "Mediator.h"
#include "WalletMediator.h"
#include "Vendor.h"

// Initialize singleton to nullptr.
World *World::_instance = nullptr;

// Singleton management function.
World *World::Instance()
{
    if (_instance == 0)
    {
        _instance = new World;
    }

    return _instance;
}

// Initialize world and other necessary variables.
World::World() :
    m_gameRunning(true)
{
    // Step 1. Init mediator for player and vendor.
    m_pMediator = new Mediator;
    // Step 2. Init mediator for enemies and players wallet.
    m_pWalletMediator = new WalletMediator;
    // Step 3. Init player.
    m_pPlayer = new Player(k_columns, k_rows);
    // Step 4. Get Players wallet and register it in the WalletMediator.
    m_pWalletMediator->RegisterParticipant(m_pPlayer->GetWallet());
    // Step 5. Init vendor.
    m_pVendor = new Vendor(m_pMediator);
    // Step 6. Register player with first mediator.
    m_pMediator->RegisterParticipant(m_pPlayer);
    // Step 7. Register Vendor with first mediator.
    m_pMediator->RegisterParticipant(m_pVendor);
    // Step 8. Init enemy management pointer.
    m_pEnemyManagement = new EnemyManagement(k_rows, k_columns);
}

// Create game board and align outer lines of it.
void World::CreateWorld()
{
    // Step 1. Assign memory to pointer.
    m_ppSpace = new Entities*[k_columns * k_rows];

    // Step 2. Set to nullptr.
    for (int i = 0; i < k_columns * k_rows; ++i)
    {
        m_ppSpace[i] = nullptr;
    }

    // Step 3. Set the top border.
    for (int x = 0; x < k_rows; ++x)
    {
        for (int y = 0; y < k_columns; ++y)
        {
            int index = (x * k_columns) + y;
            if (index < k_columns)
            {
                m_ppSpace[index] = new Border;
            }
        }
    }

    // Step 4. Set bottom border.
    int max = k_columns * k_rows;
    int position = max - (k_columns - 1);
    for (int i = position; i < max; ++i)
    {
        m_ppSpace[position] = new Border;
        ++position;
    }

    // Step 5. Set the left border.
    for (int i = k_columns; i < k_columns * k_rows; i += k_columns)
    {
        m_ppSpace[i] = new Border;
    }

    // Step 6. Set the right border.
    for (int i = 2; i < k_rows; ++i)
    {
        int pos = k_columns * i - 1;
        m_ppSpace[pos] = new Border;
    }

    // Step 7. Work on inner layer of game board.
    for (int x = 0; x < k_rows; ++x)
    {
        for (int y = 0; y < k_columns; ++y)
        {
            int index = (x * k_columns) + y;
            if (m_ppSpace[index] == nullptr)
            {
                m_ppSpace[index] = new Dots;
            }
        }
    }

    // Step 8. Generate the waves of enemies.
    m_pEnemyManagement->GenerateEnemies();
}

void World::MoveToNextLevel()
{
    // Step 1. Check if enemy vector is empty, if so, all enemies are dead. If not, exit function early.
    if (!m_pEnemyManagement->EnemiesDead())
        return;

    // Step 2. Deliver message to player.
    std::cout << "Wave " << m_pEnemyManagement->GetWaveManager()->GetCurrentWave() << " cleared!\n\n\n";
    std::cout << "Press <enter> to shop at Vendor for Weapons & Upgrades!\n";
    _getch();

    // Step 3. Open vendor.
    m_pMediator->OpenVendorShop(m_pPlayer);

    // Step 4. When Step 2 is done, advance to next wave if player didn't beat final wave. If they did, terminate game and exit function early.
    if (m_pEnemyManagement->GetWaveManager()->NextWave())
    {
        TerminateGame();
        return;
    }

    // (Optional Step) If Step 3 didn't terminate, generate new waves of enemies.
    m_pEnemyManagement->GenerateEnemies();
}

bool World::DrawBullets(int x, int y)
{
    if (m_pPlayer->DrawBullets(x, y))
        return true;

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

void World::UpdateWorld()
{
    for (int x = 0; x < k_rows; ++x)
    {
        for (int y = 0; y < k_columns; ++y)
        {
            if (DrawPlayer(x, y))
                continue;

            if (DrawBullets(x, y))
                continue;

            if (m_pEnemyManagement->DrawEnemy(x, y))
                continue;

            int index = (x * k_columns) + y;
            m_ppSpace[index]->Draw();
        }
        std::cout << "\n";
    }
}

void World::UpdateBullets()
{
    m_pPlayer->UpdateBullets();
}

void World::Update()
{
    // Step 1. Check if current enemies are all dead. 
    MoveToNextLevel();
    
    // Step 2. Step 1 might terminate the game due to player beating last level. Exit this function early if true.
    if (!CheckIsGameRunning())
        return;

    m_pEnemyManagement->UpdateEnemyMovement();

    UpdateWorld(); 

    UpdateBullets();

    m_pPlayer->DrawControls();

    m_pPlayer->DrawStats();

    if (!m_pPlayer->UpdatePlayer())
    {
        m_gameRunning = false;
        return;
    }

    system("cls");
}

std::pair<int, int> World::GetPlayerPosition() const
{
    return std::make_pair(m_pPlayer->GetY(), m_pPlayer->GetX());
}

int World::GetPlayerCurrency() const
{
    return m_pMediator->GetPlayerMoney(m_pVendor);
}

void World::DeleteWorld()
{
    ObjectPool::GetInstance()->DeletePool();

    delete m_pEnemyManagement;
    m_pEnemyManagement = nullptr;

    for (int i = 0; i < k_columns * k_rows; ++i)
    {
        delete m_ppSpace[i];
    }

    delete m_pPlayer;
    m_pPlayer = nullptr;

    m_pVendor->DeleteVendor();
    delete m_pVendor;
    m_pVendor = nullptr;

    delete m_pMediator;
    m_pMediator = nullptr;

    delete m_pWalletMediator;
    m_pWalletMediator = nullptr;

    delete m_pVendor;
    m_pVendor = nullptr;

    delete[] m_ppSpace;
    m_ppSpace = nullptr;

    delete _instance;
    _instance = nullptr;
}