// EnemyManagement.cpp
#include "EnemyManagement.h"
#include "WaveManager.h"
#include "Enemies.h"
#include "WalletMediator.h"
#include "World.h"

EnemyManagement::EnemyManagement()
{
    // Step 1. Init wave manager. WaveManager will assist in handling the waves of enemies for every level.
    m_pWaveManager = new WaveManager;
}

// World.cpp will need access to WaveManager.
WaveManager * EnemyManagement::GetWaveManager()
{
    return m_pWaveManager;
}

// BulletAlgorithm.cpp and CalculateMove.cpp will need access to the enemies vector.
std::vector<class Enemies*> EnemyManagement::GetEnemies() const
{
    return m_pEnemies;
}

// The current level is over if all enemies are dead on that level.
bool EnemyManagement::EnemiesDead() const
{
    if (!m_pEnemies.empty())
        return false;

    return true;
}

// Generate enemies for player to fight.
void EnemyManagement::GenerateEnemies()
{
    for (int i = 0; i < k_maxEnemiesPerWave; ++i)
    {
        // Step 1. Request enemy type from WaveManager, get the enemy from factory in Enemies.cpp, and save enemy in vector.
        m_pEnemies.push_back(Enemies::GetEnemy(m_pWaveManager->RequestEnemyType()));

        // Step 2. Enemies need to communicate with the players wallet to award the player money in an efficient manner.
        World::Instance()->GetWalletMediator()->RegisterParticipant(m_pEnemies.at(i));

        // Step 3. Init the enemy.
        m_pEnemies.at(i)->Init();

        // Step 4. Increase total amount of enemies.
        ++m_totalEnemies;
    }
}

// Remove the recently dead enemies from mediator, grant player money, and delete enemy from vector.
int EnemyManagement::UpdateEnemyLives()
{
    for (int i = 0; i < m_totalEnemies; ++i)
    {
        if (!m_pEnemies.at(i)->IsAlive())
        {
            // Step 1. Remove the enemy from the mediator.
            World::Instance()->GetWalletMediator()->RemoveParticipant(m_pEnemies.at(i));

            // Step 2. Collect funds from enemy to pass onto players wallet.
            World::Instance()->GetWalletMediator()->AddFundsToPlayersWallet(m_pEnemies.at(i)->AwardMoney());

            // Step 3. Delete the enemy.
            Enemies *pDelete = m_pEnemies.at(i);
            delete pDelete;
            pDelete = nullptr;

            // Step 4. Erase enemy from vector.
            m_pEnemies.erase(m_pEnemies.begin() + i);
            --m_totalEnemies;
        }
    }

    return m_totalEnemies;
}

void EnemyManagement::UpdateEnemyMovement()
{
    for (int i = 0; i < m_totalEnemies; ++i)
    {
        m_pEnemies.at(i)->Move();
    }
}

bool EnemyManagement::DrawEnemy(int x, int y) const
{
    for (int i = 0; i < m_totalEnemies; ++i)
    {
        if (x == m_pEnemies.at(i)->GetY()
            && y == m_pEnemies.at(i)->GetX())
        {
            m_pEnemies.at(i)->Draw();
            return true;
        }
    }

    return false;
}

EnemyManagement::~EnemyManagement()
{
    // Step 1. Delete all enemies.
    for (std::vector<Enemies*>::iterator it = m_pEnemies.begin(); it != m_pEnemies.end(); ++it)
    {
        delete (*it);
    }

    // Step 2. Clear the vector.
    m_pEnemies.clear();

    // Step 3. Delete wave manager.
    delete m_pWaveManager;
    m_pWaveManager = nullptr;
}
