// ObjectPool.cpp
#include "ObjectPool.h"
#include "Bullets.h"
#include "World.h"
#include "Entities.h"
#include "PistolBullet.h"
#include "ShotgunBullet.h"
#include "Rocket.h"
#include <vector>

ObjectPool *ObjectPool::m_pInstance = 0;

void ObjectPool::EmptyVector(std::vector<Entities*> pVec)
{
    // Step 1. Check if the vector is already empty, if so, return.
    if (pVec.empty())
        return;

    // Step 2. If Step 1 didn't return early, loop through vector and delete everything.
    for (auto it = std::begin(pVec); it != std::end(pVec); ++it)
    {
        delete (*it);
        *it = nullptr;
    }

    pVec.clear();
}

Entities * ObjectPool::InsertBulletInVec(std::vector<Entities*> *pVector, int bulletType)
{
    for (int i = 0; i < k_maxEmptyRequests; ++i)
    {
        pVector->insert(pVector->begin() + i, Bullets::GetBullet(bulletType));
        return pVector->at(i);
    }

    return nullptr;
}

bool ObjectPool::IsListEmpty(std::list<class Entities*> pList) const
{
    if (pList.empty())
        return true; 

    return false;
}

Entities * ObjectPool::GetPistolBullet(int bulletType)
{
    if (IsListEmpty(m_pPistolBullets))
    {
        return InsertBulletInVec(&m_pEmptyRequestsPistol, bulletType);
    }

    Entities *pPistolBullet = m_pPistolBullets.front();
    m_pPistolBullets.pop_front();
    return pPistolBullet;
}

Entities * ObjectPool::GetShotgunBullet(int bulletType)
{
    if (IsListEmpty(m_pShotgunBullets))
    {
        return InsertBulletInVec(&m_pEmptyRequestsShotgun, bulletType);
    }
    
    Entities *pShotgunBullet = m_pShotgunBullets.front(); // Crash here.
    m_pShotgunBullets.pop_front();
    return pShotgunBullet;
}

Entities * ObjectPool::GetRocket(int bulletType)
{
    if (IsListEmpty(m_pRockets))
    {
        return InsertBulletInVec(&m_pEmptyRequestsPistol, bulletType);
    }

    Entities *pRocket = m_pRockets.front();
    m_pRockets.pop_front();
    return pRocket;
}

ObjectPool * ObjectPool::GetInstance()
{
    if (m_pInstance == 0)
    {
        m_pInstance = new ObjectPool;
    }

    return m_pInstance;
}

Entities * ObjectPool::GetBullet(int bulletType)
{
    // Step 1. Determine the bullet type.
    switch (bulletType)
    {
    case 0:
        return GetPistolBullet(bulletType);
    case 1:
        return GetShotgunBullet(bulletType);
    case 2:
        return GetRocket(bulletType);
    default:
        break;
    }

    return nullptr;
}

void ObjectPool::ReturnBullet(Entities *pBullet)
{
    switch (pBullet->GetId())
    {
    case 0:
        // Return pistol bullet.
        m_pPistolBullets.push_back(pBullet);
        break;
    case 1:
        // Return shotgun bullet.
        m_pShotgunBullets.push_back(pBullet);
        break;
    case 2:
        // Return rocket.
        m_pRockets.push_back(pBullet);
        break;
    default:
        std::cout << "Error! [ObjectPool.cpp]\n";
    }
}

void ObjectPool::DeletePool()
{
    EmptyVector(m_pEmptyRequestsPistol);
    EmptyVector(m_pEmptyRequestsShotgun);
    EmptyVector(m_pEmptyRequestsRocket);

    delete m_pInstance;
    m_pInstance = nullptr;
}