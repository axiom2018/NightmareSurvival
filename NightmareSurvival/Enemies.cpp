// Enemies.cpp
#include "Enemies.h"
#include "Skeleton.h"
#include "Vampire.h"
#include "Demon.h"
#include "Boss.h"
#include "World.h"
#include "Definitions.h"
#include <iostream>

// Enemy system uses factory pattern.

Enemies * Enemies::GetEnemy(int type)
{
    switch (type)
    {
    case 0:
        return new Skeleton;
    case 1:
        return new Vampire;
    case 2:
        return new Demon;
    case 3:
        return new Boss;
    default:
        break;
    }

    return nullptr;
}

int Enemies::GetMaxEnemies()
{
    return MAX_ENEMIES;
}