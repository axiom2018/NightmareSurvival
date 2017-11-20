// Bullets.h
#pragma once
#include "Entities.h"

// Factory pattern referenced in BulletManager.cpp and ObjectPool.cpp.

class Bullets 
{
public:
    static Entities *GetBullet(int type);
};