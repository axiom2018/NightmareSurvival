// Spawn.h
#pragma once
#include "EnemyAlgorithms.h"
#include <iostream>
#include <vector>

// Calculate enemy spawn position.

class Spawn : public EnemyAlgorithms
{
    std::vector<std::pair<int, int>> m_enemyOccupiedPositions;

    int m_spawnDirection;
    int m_maxWidth;
    int m_maxHeight;

    void AddPosition(std::pair<int, int> newPosition);
    bool CheckForDuplicatePosition(std::pair<int, int> newPosition);
    bool PositionCheck(int *y, int *x);
    bool IsVectorEmpty(int *y, int *x);
    void EastSP(int *y, int *x);
    void WestSP(int *y, int *x);
    void SouthSP(int *y, int *x);
    void NorthSP(int *y, int *x);
    void SetSpawnDirection(int *y, int *x);
public:
    Spawn();
    virtual void SpawnPoint(int *y, int *x, int width, int height) override;
};