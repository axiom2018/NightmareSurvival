// WaveManagerRequestEnemyStrategy.h
#pragma once
#include "Waves.h"

/* Strategy pattern used to assist WaveManager.cpp when filling in a request from World.cpp, to return the type of Enemy that World.cpp
will get. If the current wave of enemies is anything BUT wave four and wave five, we give the wave back in int form. If it's four, we 
return a random number, and if it's five, return the max number of enemies. The strategy pattern is perfect for each of these options
to lay out. */

class WaveManagerRequestEnemyStrategy
{
public:
    virtual int ReturnTypeOfEnemy(Waves curWave) = 0;
};