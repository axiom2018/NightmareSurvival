// BulletAlgorithm.cpp
#include "BulletManager.h"
#include "ObjectPool.h"
#include "World.h" 
#include "EnemyManagement.h"
#include "Entities.h"
#include "Player.h"
#include "Directions.h"
#include "Enemies.h"
#include <string>

// Factory pattern for game upgrades.

BulletManager::BulletManager() :
    m_index(-1),
    m_amountOfEnemies(0)
{
    m_width = World::Instance()->GetWidth();
    m_height = World::Instance()->GetHeight();
}

BulletManager::~BulletManager()
{
    m_pBullets.clear();
}

bool BulletManager::CheckBulletBize()
{
    if (m_pBullets.empty())
        return true;

    return false;
}

void BulletManager::SetData()
{
    m_x = World::Instance()->GetPlayer()->GetX();
    m_y = World::Instance()->GetPlayer()->GetY();

    m_direction = World::Instance()->GetPlayer()->GetDirection(); 
}

void BulletManager::AlterData()
{
    switch (m_direction)
    {
    case Directions::North:
        m_y -= 1;
        m_pBullets.at(m_index)->SetDirection(Directions::North);
        break;
    case Directions::West:
        m_x -= 1;
        m_pBullets.at(m_index)->SetDirection(Directions::West);
        break;
    case Directions::South:
        m_y += 1;
        m_pBullets.at(m_index)->SetDirection(Directions::South);
        break;
    case Directions::East:
        m_x += 1;
        m_pBullets.at(m_index)->SetDirection(Directions::East);
        break;
    default:
        std::cout << "Error! AlterData() [BulletManager.cpp]\n";
    }

    m_pBullets.at(m_index)->SetX(m_y);
    m_pBullets.at(m_index)->SetY(m_x);
}

void BulletManager::RequestBullet(int weaponId)
{
    switch (weaponId)
    {
    case 0: // Pistol bullet.
        m_pBullets.push_back(ObjectPool::GetInstance()->GetBullet(weaponId)); 
        ++m_index;
        break;
    case 1: // Shotgun bullet.
        m_pBullets.push_back(ObjectPool::GetInstance()->GetBullet(weaponId)); 
        ++m_index;
        break;
    case 2: // Rocket.
        m_pBullets.push_back(ObjectPool::GetInstance()->GetBullet(weaponId));
        ++m_index;
        break;
    default:
        std::cout << "Error! BulletManager(int weaponId) [BulletManager.cpp]\n";
    }

    SetData();
    AlterData();
}

void BulletManager::CheckForEnemyCollision(int *pBulletIndex)
{
    for (int i = 0; i < m_amountOfEnemies; ++i)
    {
        // Step 1. Check if enemy is in range of being hit.
        if (m_bulletY == m_pSaveEnemies.at(i)->GetX() 
            && m_bulletX == m_pSaveEnemies.at(i)->GetY())
        {
            // Step 2. If step 1 passed, decrease the enemy's health by the bullet damage.
            m_pSaveEnemies.at(i)->DecreaseHealth(m_pBullets.at(*pBulletIndex)->GetBulletDamage());

            // Step 3. Return the bullet to the pool.
            ObjectPool::GetInstance()->ReturnBullet(m_pBullets.at(*pBulletIndex));
            m_pBullets.erase(m_pBullets.begin() + *pBulletIndex);
            --m_index;

            // Step 4. Must get the correct amount of enemies since one just died, and adjust variables accordingly.
            m_amountOfEnemies = World::Instance()->GetEnemyManager()->UpdateEnemyLives();
            --*pBulletIndex;
            --m_bulletSize;

            // Step 5. Update enemies after kill to make sure our m_pSaveEnemies vector doesn't access a deleted enemy that was nullptr.
            m_pSaveEnemies = World::Instance()->GetEnemyManager()->GetEnemies();
            m_amountOfEnemies = m_pSaveEnemies.size();

            break;
        }
    }
}

void BulletManager::SetBulletPos(int bulletIndex)
{
    m_bulletY = m_pBullets.at(bulletIndex)->GetY();
    m_bulletX = m_pBullets.at(bulletIndex)->GetX();
}

void BulletManager::DetermineBulletDirection(int bulletIndex)
{
    /* The next bullet position system is out right now.


    // Step 1. Bullet is traveling in one of the 4 directions. Begin algorithm by checking which.
    switch (m_pBullets.at(bulletIndex)->GetDirection())
    {
    case Directions::North:
        m_nextBulletPos = m_pBullets.at(bulletIndex)->GetX() - 1;
        break;
    case Directions::West:
        m_nextBulletPos = m_pBullets.at(bulletIndex)->GetY() - 1;
        break;
    case Directions::East:
        m_nextBulletPos = m_pBullets.at(bulletIndex)->GetY() + 1;
        break;
    case Directions::South:
        m_nextBulletPos = m_pBullets.at(bulletIndex)->GetX();
        break;
    default:
        std::cout << "Error! DetermineBulletDirection(int bulletIndex) [BulletManager.cpp]\n";
    }
    */

    // Step 2. Set the bullet position.
    SetBulletPos(bulletIndex);
}

bool BulletManager::EnemyCollision()
{
    // Step 1. Grab all enemies and size of enemies.
    m_pSaveEnemies = World::Instance()->GetEnemyManager()->GetEnemies(); 
    m_amountOfEnemies = m_pSaveEnemies.size();

    int i = 0;

    // Step 2. Check bullet size.
    if (CheckBulletBize())
        return false;

    // Step 3. If step 2 doesn't return, get size of bullets.
    m_bulletSize = m_pBullets.size();

    // Step 4. Loop.
    for (i; i < m_bulletSize; ++i)
    {
        DetermineBulletDirection(i);
        CheckForEnemyCollision(&i);
    }

    return false;
}

bool BulletManager::DrawBullets(int x, int y)
{
    /// Do EC before or after we draw bullets?. Before sounds reasonable.
    EnemyCollision();

    // Step 1. Check bullet size.
    if (CheckBulletBize())
        return false;

    // Step 2. Draw bullets if necessary.
    for (std::vector<Entities*>::iterator iter = m_pBullets.begin(); iter != m_pBullets.end(); ++iter)
    {
        if (x == (*iter)->GetX() &&
            y == (*iter)->GetY())
        {
            (*iter)->Draw();
            return true;
        }
    }

    return false;
}

void BulletManager::ReturnBullet(int *pBulletIndex)
{
    ObjectPool::GetInstance()->ReturnBullet(m_pBullets.at(*pBulletIndex));
    m_pBullets.erase(m_pBullets.begin() + *pBulletIndex);
    --m_index;
    --m_size;
    *pBulletIndex -= 1;
}

void BulletManager::SouthBulletUpdate(int *pBulletIndex)
{
    // Step 1. Save the desired position of the bullet in a variable and save wall limit.
    int limit = m_height - 2;
    int temp = m_pBullets.at(*pBulletIndex)->GetX();

    // Step 2. If bullet collides with wall, return it to ObjectPool.
    if (temp >= limit)
    {
        ReturnBullet(pBulletIndex);
        return;
    }

    // Step 3. If step 2 fails, update bullet.
    m_pBullets.at(*pBulletIndex)->Update();
}

void BulletManager::EastBulletUpdate(int *pBulletIndex)
{
    // Step 1. Save the desired position of the bullet in a variable and save wall limit.
    int temp = m_pBullets.at(*pBulletIndex)->GetY() + 1;
    int wall = m_width - 1;

    // Step 2. If bullet collides with wall, return it to ObjectPool.
    if (temp >= wall)
    {
        ReturnBullet(pBulletIndex);
        return;
    }

    // Step 3. If step 2 fails, update bullet.
    m_pBullets.at(*pBulletIndex)->Update();
}

void BulletManager::WestBulletUpdate(int *pBulletIndex)
{
    // Step 1. Save the desired position of the bullet in a variable and see if it's available.
    int pos = m_pBullets.at(*pBulletIndex)->GetY() - 1;

    if (pos <= 0)
    {
        ReturnBullet(pBulletIndex);
        return;
    }

    m_pBullets.at(*pBulletIndex)->Update();
}

void BulletManager::NorthBulletUpdate(int *pBulletIndex)
{
    // Step 1. Save the desired position of the bullet in a variable and see if it's available.
    int pos = m_pBullets.at(*pBulletIndex)->GetX() - 1;

    if (pos <= 0)
    {
        ReturnBullet(pBulletIndex);
        return;
    }

    m_pBullets.at(*pBulletIndex)->Update();
}

void BulletManager::BulletUpdate(int *pBulletIndex)
{
    switch (m_pBullets.at(*pBulletIndex)->GetDirection())
    {
    case Directions::North:
        NorthBulletUpdate(pBulletIndex);
        break;
    case Directions::West:
        WestBulletUpdate(pBulletIndex);
        break;
    case Directions::East:
        EastBulletUpdate(pBulletIndex);
        break;
    case Directions::South:
        SouthBulletUpdate(pBulletIndex);
        break;
    default:
        std::cout << "Error! [BulletManager.cpp]\n";
    }
}

void BulletManager::UpdateBullets()
{
    // Step 1. If the vector is empty, return. Nothing to update.
    if (CheckBulletBize())
        return;

    // Step 2. Get amount of bullets.
    m_size = m_pBullets.size();

    // Step 3. Begin bullet updates.
    int i;
    for (i = 0; i < m_size; ++i)
    {
        // Step 4. Decide direction on bullet.
        BulletUpdate(&i);
    }
}