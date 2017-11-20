// RandomWave.cpp 
#include "RandomWave.h"
#include "Enemies.h"
#include <iostream>

int RandomWave::ReturnTypeOfEnemy(Waves curWave)
{
    return (0 + rand() % Enemies::GetMaxEnemies());
}
