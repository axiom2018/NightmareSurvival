// FinalWave.h
#pragma once
#include "WaveManagerRequestEnemyStrategy.h"

// FinalWave will inform World.cpp to create all boss level enemies.

class FinalWave : public WaveManagerRequestEnemyStrategy
{
public:
    virtual int ReturnTypeOfEnemy(Waves curWave) override;
};