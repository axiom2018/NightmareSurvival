// RandomWave.h
#pragma once
#include "WaveManagerRequestEnemyStrategy.h"

// RandomWave will be responsible for using randomness to determine what enemy World.cpp will create.

class RandomWave : public WaveManagerRequestEnemyStrategy
{
public:
    virtual int ReturnTypeOfEnemy(Waves curWave) override;
};
