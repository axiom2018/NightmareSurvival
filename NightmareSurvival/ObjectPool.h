// ObjectPool.h
#pragma once
#include <iostream>
#include <list>
#include <queue>

class ObjectPool
{
private:
    static ObjectPool * m_pInstance;
    std::vector<class Entities*> m_pBullets;
    class Entities * GetBulletByType(int type);
    ObjectPool() {};
public:
    static ObjectPool * GetInstance();
    class Entities * GetBullet(int bulletType);
    void ReturnBullet(class Entities *pBullet);
    void DeletePool();
};

