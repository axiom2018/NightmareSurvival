// CalculateMove.cpp
#include "CalculateMove.h"
#include "World.h" 
#include <iostream>
#include "Player.h"
#include "Enemies.h"
#include "Entities.h"
#include "Border.h"
#include "Altitudes.h"
#include "EnemyManagement.h"
#include "ManageEnemyPosition.h"

// Initialize settings with constructor.
CalculateMove::CalculateMove(int enemySpeedDelay, int enemyDamage)
{
    // Step 1. Set variables.
    m_delay = enemySpeedDelay;
    m_maxDelay = enemySpeedDelay;
    m_enemyDamage = enemyDamage;

    // Step 2. Initialize ManageEnemyPosition.
    m_pManageEnemyPosition = new ManageEnemyPosition;
}

// Send damage to player.
void CalculateMove::ApplyDamage(int *x, int *y)
{
    // Step 1. Get player position.
    int playerX = World::Instance()->GetPlayer()->GetX();
    int playerY = World::Instance()->GetPlayer()->GetY();

    // Step 2. Check if player position matches enemy position, if so, apply damage.
    if (playerX == *x
        && playerY == *y)
    {
        World::Instance()->GetPlayer()->Damage(m_enemyDamage);
    }
}


// Part of movement delay test.
bool CalculateMove::DelayCheck()
{
    if (m_delay != 0)
    {
        --m_delay;
        return false;
    }

    return true;
}

void CalculateMove::CalculateEnemyMove(int *x, int *y)
{
    // Step 1. Check delay.
    if (!DelayCheck())
        return;

    // Step 2. Reset the delay speed.
    m_delay = m_maxDelay;

    // Step 3. Continue with move calculation process by getting player position.
    Coordinates playerPos; 
    playerPos.first = World::Instance()->GetPlayer()->GetX();
    playerPos.second = World::Instance()->GetPlayer()->GetY();

    // Step 4. Check the x position.
    m_pManageEnemyPosition->FindVacantPosition(playerPos, x, y);

    // Step 5. Apply damage if necessary.
    ApplyDamage(x, y);
}

// Free up memory in destructor.
CalculateMove::~CalculateMove()
{
    delete m_pManageEnemyPosition;
    m_pManageEnemyPosition = nullptr;
}
