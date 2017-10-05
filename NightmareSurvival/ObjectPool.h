// ObjectPool.h
#pragma once
#include <iostream>
#include <list>
#include <queue>

class ObjectPool
{
private:
    static ObjectPool *m_pInstance;
    const int k_maxEmptyRequests = 25; // You'll never be able to reach 25 bullets without any pool filling up so you can RE-USE the bullets.
    std::list<class Entities*> m_pPistolBullets;
    std::list<class Entities*> m_pShotgunBullets;
    std::list<class Entities*> m_pRockets;
    std::vector<class Entities*> m_pEmptyRequestsPistol;
    std::vector<class Entities*> m_pEmptyRequestsShotgun;
    std::vector<class Entities*> m_pEmptyRequestsRocket;

    void EmptyVector(std::vector<class Entities*> pVec);
    class Entities *InsertBulletInVec(std::vector<Entities*> *pVector, int bulletType);
    bool IsListEmpty(std::list<class Entities*> pList) const;
    class Entities *GetPistolBullet(int bulletType);
    class Entities *GetShotgunBullet(int bulletType);
    class Entities *GetRocket(int bulletType);

    ObjectPool() {};
public:
    static ObjectPool *GetInstance();
    class Entities *GetBullet(int bulletType);
    void ReturnBullet(class Entities *pBullet);
    void DeletePool();
};

