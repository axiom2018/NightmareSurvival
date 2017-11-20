// WaveManager.cpp
#include "WaveManager.h"
#include "Enemies.h"
#include "WaveManagerRequestEnemyStrategy.h"
#include "CurrentWave.h"
#include "RandomWave.h"
#include "FinalWave.h"
#include <iostream>

// Initialize settings with constructor.
WaveManager::WaveManager() :
    m_currentWave(0),
    m_curWave(Waves::WaveOne)
{
    // Set up strategy for deciding which type of enemy World will make here.
    m_pEnemyTypeStrategy = new CurrentWave;
}

int WaveManager::GetCurrentWave() const
{
    return (int)m_curWave + 1;
}

bool WaveManager::IsGameOver() const
{
    if (m_curWave == Waves::WaveFive)
        return true;

    return false;
}

bool WaveManager::NextWave()
{
    // Step 2. Check for game over.
    if (IsGameOver())
        return true;

    // Step 1. If step 1 is false, proceed to next level.
    ++m_currentWave;
    m_curWave = static_cast<Waves>(m_currentWave);

    return false;
}

// Depending on the wave, certain enemies will be created. Using strategy pattern.
int WaveManager::RequestEnemyType()
{
    // Step 1. Before we declare new on which strategy we want, delete the old one to free up that allocated memory.
    delete m_pEnemyTypeStrategy;
    m_pEnemyTypeStrategy = nullptr;

    // Step 2. Decide which strategy to go with.
    if (m_curWave == Waves::WaveFour)
    {
        m_pEnemyTypeStrategy = new RandomWave;
    }

    else if (m_curWave == Waves::WaveFive)
    {
        m_pEnemyTypeStrategy = new FinalWave;
    }

    else
    {
        m_pEnemyTypeStrategy = new CurrentWave;
    }

    // Step 3. Carry out strategy orders and return it.
    return m_pEnemyTypeStrategy->ReturnTypeOfEnemy(m_curWave);
}

WaveManager::~WaveManager()
{
    delete m_pEnemyTypeStrategy;
    m_pEnemyTypeStrategy = nullptr;
}
