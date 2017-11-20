// ManageEnemyPosition.h
#pragma once
#include <vector>
#include "Coordinates.h"

// Delegate responsibility of changing enemy position here.

class ManageEnemyPosition
{
private:
    class CheckArea *m_pCheckArea;
    Coordinates m_savePlayerPos;
    Coordinates m_desiredPosition;
    std::vector<class Enemies*> m_pSaveEnemies;
    std::vector<Coordinates> m_enemyPositions;

    bool CheckEnemySize() const;
    bool IsPositionTaken(int x, int y);
    void AppointPosition(int *x, int *y);
    void CheckRight(Coordinates player, int *x, int *y);
    void CheckMiddle(Coordinates player, int *x, int *y);
    void CheckLeft(Coordinates player, int *x, int *y);
    void CheckXPos(Coordinates player, int *x, int *y);

public:
    ManageEnemyPosition();
    void FindVacantPosition(Coordinates player, int *x, int *y);
    ~ManageEnemyPosition();
};