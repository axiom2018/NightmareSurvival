// CalculateMove.h
#pragma once
#include "EnemyAlgorithms.h"
#include "Definitions.h"
#include <iostream>
#include <vector>

// Calculate where the enemy should move next.

class CalculateMove : public EnemyAlgorithms
{
private:
    int m_delay;
    int m_maxDelay;
    int m_enemyDamage;
    class ManageEnemyPosition *m_pManageEnemyPosition;
    bool DelayCheck();
    void ApplyDamage(int *x, int *y);
public:
    CalculateMove(int enemySpeedDelay, int enemyDamage);
    virtual void CalculateEnemyMove(int *x, int *y) override;
    ~CalculateMove();
};

