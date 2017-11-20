// CheckArea.h
#pragma once
#include "Definitions.h"
#include "Altitudes.h"
#include "Coordinates.h"

// If logical position for enemy to move is taken, find available vacant positions around the enemy to move to.

class CheckArea
{
    // Function pointers are used to fully complete the process of the enemy finding a new position. Delegate that task here.
    typedef bool (CheckArea::*PositionPrerequisiteTest)(int index);
    PositionPrerequisiteTest PrereqTests[MAX_PREREQ_TESTS];
    typedef bool (CheckArea::*PrimaryTest)(int *x, int *y);
    PrimaryTest PrimaryPositionTest[MAX_POSITION_TESTS];

    std::vector<Coordinates> *m_pEnemyCoordinates;

    bool BorderCheck(int index);
    bool EnemiesCheck(int index);
    void AppointLowPosition(int arrIndex, int *x, int *y);
    void AppointMidPosition(int arrIndex, int *x);
    void AppointHighPosition(int arrIndex, int *x, int *y);
    void ResolveAltitude(EnemyAltitudes alt, int arrIndex, int *x, int *y);
    bool AltitudeCheckAssistance(int posArr[], int arrSize, int outerLoop, int innerLoop, int *x, int *y, EnemyAltitudes alt);
    bool CheckHigh(int *x, int *y);
    bool CheckMid(int *x, int *y);
    bool CheckLow(int *x, int *y);
public:
    CheckArea(std::vector<Coordinates> *pEnemyCoordinates);
    bool CheckSurroundingArea(int *x, int *y);
};