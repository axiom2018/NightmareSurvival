// CurrentWave.h 
#pragma once
#include "WaveManagerRequestEnemyStrategy.h"

// CurrentWave will make a decision on what type of enemy World.cpp will get, based on the current wave (in WaveManager.h).

class CurrentWave : public WaveManagerRequestEnemyStrategy
{
public:
    virtual int ReturnTypeOfEnemy(Waves curWave) override;
};
