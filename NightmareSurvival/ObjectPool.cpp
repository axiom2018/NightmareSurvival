// ObjectPool.cpp
#include "ObjectPool.h"
#include "Bullets.h"
#include "World.h"
#include "Entities.h"
#include "PistolBullet.h"
#include "ShotgunBullet.h"
#include "Rocket.h"
#include "Definitions.h"
#include <vector>

// Initialize singleton to nullptr.
ObjectPool *ObjectPool::m_pInstance = nullptr;

// Singleton management function.
ObjectPool * ObjectPool::GetInstance()
{
    if (m_pInstance == 0)
    {
        m_pInstance = new ObjectPool;
    }

    return m_pInstance;
}

// Find the bullet we want by the type we pass as an argument.
class Entities * ObjectPool::GetBulletByType(int type)
{
    // Step 1. Get size ready for loop.
    int size = m_pBullets.size();

    // Step 2. Begin loop.
    for (int i = 0; i < size; ++i)
    {
        // Step 3. Check if bullet is correct type.
        if (m_pBullets.at(i)->GetId() == type)
        {
            // (Optional Step) Save the bullet. 
            Entities *pBullet = m_pBullets.at(i);
            // (Optional Step) Erase the bullet from the vector.
            m_pBullets.erase(m_pBullets.begin() + i); 
            // (Optional Step) Return bullet.
            return pBullet;
        }
    }

    // (Optional Step) Return nullptr if the vector has no bullets of the type requested.
    return nullptr;
}

// Bullet is requested by the BulletManager.cpp file.
Entities * ObjectPool::GetBullet(int bulletType)
{
    // Step 1. If bullet reserve is empty, get fresh one.
    if (m_pBullets.empty())
    {
        return Bullets::GetBullet(bulletType);
    }

    else
    {
        // Step 2. We have a bullet(s) in the reserve, get one.
        Entities *pBullet = GetBulletByType(bulletType);

        if (pBullet)
        {
            // (Optional Step) GetBulletByType() has not returned nullptr. This is a valid bullet. Return it.
            return pBullet;
        }

        else
        {
            // (Optional Step) GetBulletByType() has returned nullptr. The bullet wasn't find. Get the type requested.
            return Bullets::GetBullet(bulletType);
        }

    }

    return nullptr;
}

// Bullet will be returned by the BulletManager.cpp file.
void ObjectPool::ReturnBullet(Entities *pBullet)
{
    m_pBullets.push_back(pBullet);
}

void ObjectPool::DeletePool()
{
    for (std::vector<Entities*>::iterator it = m_pBullets.begin(); it != m_pBullets.end(); ++it)
    {
        delete (*it);
    }

    m_pBullets.clear();

    delete m_pInstance;
    m_pInstance = nullptr;
}