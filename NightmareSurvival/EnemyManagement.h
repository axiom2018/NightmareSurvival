// EnemyManagement.h
#pragma once
#include <vector>
#include "Definitions.h"

// Manage enemies through an interface. Previous implementation made World.cpp handle enemies. Delegate that responsibility.

class EnemyManagement
{
    std::vector<class Enemies*> m_pEnemies;
    class WaveManager *m_pWaveManager;
    const int k_maxEnemiesPerWave = MAX_ENEMIES_PER_WAVE;
    int m_totalEnemies;
public:
    EnemyManagement();
    class WaveManager * GetWaveManager();
    class std::vector<class Enemies*> GetEnemies() const;
    bool EnemiesDead() const;
    void GenerateEnemies();
    int UpdateEnemyLives();
    void UpdateEnemyMovement();
    bool DrawEnemy(int x, int y) const;
    ~EnemyManagement();
};