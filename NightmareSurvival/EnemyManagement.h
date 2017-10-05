// EnemyManagement.h
#pragma once
#include <vector>

// Manage enemies through an interface. Previous implementation made World.cpp handle enemies. Delegate that responsibility.

class EnemyManagement
{
    std::vector<class Enemies*> m_pEnemies;
    class WaveManager *m_pWaveManager; // WaveManager will assist in handling the waves of enemies for every level.
    const int k_maxEnemiesPerWave = 5;
    int m_totalEnemies;
    int m_rows;
    int m_columns;
public:
    EnemyManagement(int rows, int columns);
    class WaveManager * GetWaveManager();
    class std::vector<class Enemies*> GetEnemies() const;
    bool EnemiesDead() const;
    void GenerateEnemies();
    int UpdateEnemyLives();
    void UpdateEnemyMovement();
    bool DrawEnemy(int x, int y) const;
    ~EnemyManagement();
};