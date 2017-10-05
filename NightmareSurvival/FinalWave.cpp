// FinalWave.cpp
#include "FinalWave.h"
#include "Enemies.h"

int FinalWave::ReturnTypeOfEnemy(Waves curWave)
{
    return Enemies::GetMaxEnemies();
}
