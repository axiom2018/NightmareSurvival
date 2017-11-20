// BulletAlgorithm.cpp
#include "BulletManager.h"
#include "ObjectPool.h"
#include "World.h" 
#include "EnemyManagement.h"
#include "Entities.h"
#include "Player.h"
#include "Directions.h"
#include "Enemies.h"
#include "Definitions.h"
#include <string>

// Save world coordinates in constructor.
BulletManager::BulletManager() :
    m_index(-1),
    m_amountOfEnemies(0)
{

}

bool BulletManager::CheckBulletSize()
{
    if (m_pBullets.empty())
        return true;

    return false;
}

// Start the bullet position and direction exactly as the players.
void BulletManager::SetData()
{
    m_x = World::Instance()->GetPlayer()->GetX();
    m_y = World::Instance()->GetPlayer()->GetY();

    m_direction = World::Instance()->GetPlayer()->GetDirection(); 
}

// Based on the direction, alter the position of the bullet, and set the direction.
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
        return;
    }

    m_pBullets.at(m_index)->SetX(m_y);
    m_pBullets.at(m_index)->SetY(m_x);
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

// Set bullet position.
void BulletManager::SetBulletPos(int bulletIndex)
{
    m_bulletY = m_pBullets.at(bulletIndex)->GetY();
    m_bulletX = m_pBullets.at(bulletIndex)->GetX();
}

// Set bullet direction.
void BulletManager::DetermineBulletDirection(int bulletIndex)
{
    // Step 2. Set the bullet position.
    SetBulletPos(bulletIndex);
}

// When the bullet has hit an enemy, return it to the object pool.
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
    int limit = ROWS - 2;
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
    int wall = COLUMNS - 1;

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
        return;
    }
}

// Control how bullets interact when hitting enemies.
bool BulletManager::EnemyCollision()
{
    // Step 1. Grab all enemies and size of enemies.
    m_pSaveEnemies = World::Instance()->GetEnemyManager()->GetEnemies();

    // Step 2. Get the size of the enemies.
    m_amountOfEnemies = m_pSaveEnemies.size();

    // Step 3. Check bullet size.
    if (CheckBulletSize())
        return false;

    // Step 4. If step 2 doesn't return, get size of bullets.
    m_bulletSize = m_pBullets.size();

    // Step 5. Loop.
    for (int i = 0; i < m_bulletSize; ++i)
    {
        DetermineBulletDirection(i);
        CheckForEnemyCollision(&i);
    }

    return false;
}

// Referenced in World.cpp. Will remove all traveling bullets that hit nothing after the player cleared out enemies.
void BulletManager::ReturnAllBulletsOnGameBoard()
{
    // Step 1. Check if there are bullets in the vector before continuing.
    if (CheckBulletSize())
        return;
    /*
    // Step 2. Go through the entire vector and send the bullets back to object pool.
    while (!CheckBulletSize())
    {
        // (Optional Step) Continue with operations until vector is empty.
        ObjectPool::GetInstance()->ReturnBullet(m_pBullets.front());
        // (Optional Step) Erase bullet from vector.
        m_pBullets.erase(m_pBullets.begin());
        // (Optional Step) Decrease class member variables as each bullet is returned.
        --m_index;
        --m_size;
    }
    */

    // Step 2. Get size for loop.
    int size = m_pBullets.size();

    // Step 3. Loop.
    for (int i = 0; i < size; ++i)
    {
        // (Optional Step) Save bullet in pointer.
        Entities *pBullet = m_pBullets.at(i);
        // (Optional Step) Erase bullet from vector.
        m_pBullets.erase(m_pBullets.begin() + i);
        // (Optional Step) Delete bullet.
        delete pBullet;
        // (Optional Step) Set old pointer to nullptr.
        pBullet = nullptr;
        // (Optional Step) Decrement variables.
        --m_index;
        --m_size;
    }
}

void BulletManager::UpdateBullets()
{
    // Step 1. If the vector is empty, return. Nothing to update.
    if (CheckBulletSize())
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

bool BulletManager::DrawBullets(int x, int y)
{
    // Do EC before or after we draw bullets?. Before sounds reasonable.
    EnemyCollision();

    // Step 1. Check bullet size.
    if (CheckBulletSize())
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

// Get bullet from object pool.
void BulletManager::RequestBullet(int weaponId)
{
    // Step 1. Get correct type of bullet to push back in vector.
    m_pBullets.push_back(ObjectPool::GetInstance()->GetBullet(weaponId));

    // Step 2. Increment index.
    ++m_index;

    // Step 2. Edit bullet data.
    SetData();
    AlterData();
}

BulletManager::~BulletManager()
{
    m_pBullets.clear();
}