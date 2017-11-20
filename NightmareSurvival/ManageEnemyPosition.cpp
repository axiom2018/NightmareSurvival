// ManageEnemyPosition.cpp
#include "ManageEnemyPosition.h"
#include "World.h"
#include "EnemyManagement.h"
#include "Enemies.h"
#include "CheckArea.h"

// Initialize pointer in constructor.
ManageEnemyPosition::ManageEnemyPosition() 
{
    // Step 1. Initialize the CheckArea pointer.
    m_pCheckArea = new CheckArea(&m_enemyPositions);
}

// Check if vector is empty.
bool ManageEnemyPosition::CheckEnemySize() const
{
    if (m_enemyPositions.empty())
        return true;

    return false;
}

// Check all current enemies positions with the desired position. No enemy overlapping allowed.
bool ManageEnemyPosition::IsPositionTaken(int x, int y)
{
    // Step 1. Gather enemies.
    m_pSaveEnemies = World::Instance()->GetEnemyManager()->GetEnemies();

    // Step 2. Check if vector of positions is not empty, if that's the case, clear it.
    if (!CheckEnemySize())
        m_enemyPositions.clear();

    // Step 3. Now get all the positions of the enemies.
    for (std::vector<Enemies*>::iterator it = m_pSaveEnemies.begin(); it != m_pSaveEnemies.end(); ++it)
    {
        if ((*it)->IsAlive())
        {
            m_enemyPositions.push_back(std::make_pair((*it)->GetX(), (*it)->GetY()));
        }
    }

    // Step 4. Check for matching position.
    for (std::vector<std::pair<int, int>>::iterator it = m_enemyPositions.begin(); it != m_enemyPositions.end(); ++it)
    {
        if (it->first == x && it->second == y)
        {
            return true;
        }
    }

    // (Optional Step) If no matches were found, return false.
    return false;
}

// Assign desired position for enemy, or if position is not available, find a surrounding position.
void ManageEnemyPosition::AppointPosition(int * x, int * y)
{
    if (!IsPositionTaken(m_desiredPosition.first, m_desiredPosition.second))
    {
        *x = m_desiredPosition.first;
        *y = m_desiredPosition.second;
    }

    else
    {
        m_pCheckArea->CheckSurroundingArea(x, y);
    }
}

// Based on the players x position, the player is to the right of the enemy.
void ManageEnemyPosition::CheckRight(Coordinates player, int * x, int * y)
{
    // Step 1. It's already determined in this function that the player is right of the enemy. Determine the y axis now.
    m_desiredPosition.first = *x + 1;

    // Step 2. Check if player is above, below, or on the same level as enemy.
    if (player.second < *y) 
    {
        m_desiredPosition.second = *y - 1;
    }

    else if (player.second > *y) 
    {
        m_desiredPosition.second = *y + 1;
    }

    else if (player.second == *y) 
    {
        m_desiredPosition.second = *y;
    }

    // Step 3. Attempt to assign position.
    AppointPosition(x, y);
}

// Based on the players x position, the player is on the same x position as the enemy.
void ManageEnemyPosition::CheckMiddle(Coordinates player, int * x, int * y)
{
    // Step 1. Player shares the same x axis as the enemy. Determine the y axis now.
    m_desiredPosition.first = *x;

    // Step 2. Check to see if player is above or below enemy.
    if (player.second < *y) 
    {
        m_desiredPosition.second = *y - 1;
    }

    else if (player.second > *y) 
    {
        m_desiredPosition.second = *y + 1;
    }

    // Step 3. Attempt to set position.
    AppointPosition(x, y);
}

// Based on the players x position, the player is to the left of the enemy.
void ManageEnemyPosition::CheckLeft(Coordinates player, int * x, int * y)
{
    // Step 1. It's already determined in this function that the player is left of the enemy. Determine the y axis now.
    m_desiredPosition.first = *x - 1;

    // Step 2. Check if player is above, below, or on the same level as enemy.
    if (player.second < *y)
    {
        m_desiredPosition.second = *y - 1;
    }

    else if (player.second > *y)
    {
        m_desiredPosition.second = *y + 1;
    }

    else if (player.second == *y)
    {
        m_desiredPosition.second = *y;
    }

    // Step 3. Attempt to set position.
    AppointPosition(x, y);
}

// Is player to the enemy's left, right, or is the enemy sharing the same x position?
void ManageEnemyPosition::CheckXPos(Coordinates player, int * x, int * y)
{
    if (player.first < *x)
    {
        CheckLeft(player, x, y);
    }

    else if (player.first > *x)
    {
        CheckRight(player, x, y);
    }

    else if (player.first == *x)
    {
        CheckMiddle(player, x, y);
    }
}

// Begin process of finding a vacant position for the enemy.
void ManageEnemyPosition::FindVacantPosition(Coordinates player, int * x, int * y)
{
    // Step 1. Check the X position of the player with the position of the enemy to start.
    CheckXPos(player, x, y);
}

// Free up memory in destructor.
ManageEnemyPosition::~ManageEnemyPosition()
{
    delete m_pCheckArea;
    m_pCheckArea = nullptr;
}
