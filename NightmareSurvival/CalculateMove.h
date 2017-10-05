// CalculateMove.h
#pragma once
#include "EnemyAlgorithms.h"
#include <iostream>
#include <vector>
#define MAX_POSITION_TESTS 3
#define MAX_PREREQ_TESTS 2
#define HIGH_AND_LOW_MAX 3

// Calculate where the enemy should move next.

enum EnemyAltitudes;
typedef std::pair<int, int> Coordinates;

class CalculateMove : public EnemyAlgorithms
{
private:
    bool m_initFuncPointers;
    int m_width;
    int m_height;
    int m_delay;
    int m_maxDelay;
    int m_enemyDamage;
    class Entities **m_ppWorld;
    std::pair<int, int> m_savePlayerPos;
    std::vector<class Enemies*> m_pSaveEnemies;
    std::vector<std::pair<int, int>> m_enemyPositions;
    Coordinates m_desiredPosition;

    typedef bool (CalculateMove::*PositionPrerequisiteTest)(int index);
    PositionPrerequisiteTest PrereqTests[MAX_PREREQ_TESTS];
    typedef bool (CalculateMove::*PrimaryTest)(int *x, int *y);
    PrimaryTest PrimaryPositionTest[MAX_POSITION_TESTS];

    void InitFuncPointers();
    bool CheckEnemySize() const;
    bool BorderCheck(int index);
    bool EnemiesCheck(int index);
    bool DelayCheck();
    bool CheckHigh(int *x, int *y);
    bool CheckMid(int *x, int *y);
    bool CheckLow(int *x, int *y);

    void ApplyDamage(int *x, int *y);
    void ResolveAltitude(EnemyAltitudes alt, int arrIndex, int *x, int *y);
    bool AltitudeCheckAssistance(int posArr[], int arrSize, int outerLoop, int innerLoop, int *x, int *y, EnemyAltitudes alt);
    void AppointLowPosition(int arrIndex, int *x, int *y);
    void AppointMidPosition(int arrIndex, int *x);
    void AppointHighPosition(int arrIndex, int *x, int *y);
    void AppointPosition(int *x, int *y);
    void CheckRight(Coordinates player, int *x, int *y);
    void CheckMiddle(Coordinates player, int *x, int *y);
    void CheckLeft(Coordinates player, int *x, int *y);
    void CheckXPos(Coordinates player, int *x, int *y);
    bool IsPositionTaken(int x, int y);
    bool CheckSurroundings(int *x, int *y);
public:
    CalculateMove(int enemySpeedDelay, int enemyDamage);
    virtual void CalculateEnemyMove(int *x, int *y) override;
};

