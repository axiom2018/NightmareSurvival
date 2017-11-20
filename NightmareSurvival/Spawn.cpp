// Spawn.cpp
#include "Spawn.h"
#include "World.h"
#include "Definitions.h"
#include <stdlib.h>

// Add to taken positions.
void Spawn::AddPosition(std::pair<int, int> newPosition)
{
    m_enemyOccupiedPositions.push_back(newPosition);
}

// Find duplicate spawn points.
bool Spawn::CheckForDuplicatePosition(std::pair<int, int> newPosition)
{
    for (unsigned int i = 0; i < m_enemyOccupiedPositions.size(); ++i)
    {
        if (m_enemyOccupiedPositions.at(i).first == newPosition.first
            && m_enemyOccupiedPositions.at(i).second == newPosition.second)
        {
            return true; 
        }
    }

    return false;
}

// First check for repeated/duplicate positions, if none, add to vector.
bool Spawn::PositionCheck(int *y, int *x)
{
    // Step 1. Check for duplicates, if true, return and the spawn point function chooses new position. Otherwise continue to Step 2. 
    if (CheckForDuplicatePosition(std::make_pair(*y, *x)))
        return true;

    // Step 2. Step 1 confirmed no duplicate, so it's safe to add this position.
    AddPosition(std::make_pair(*y, *x));

    return false;
}

// Check if vector is empty. If so, add point and return true.
bool Spawn::IsVectorEmpty(int *y, int *x)
{
    if (m_enemyOccupiedPositions.empty())
    {
        m_enemyOccupiedPositions.push_back(std::make_pair(*y, *x));
        return true;
    }

    return false;
}

// East spawn point.
void Spawn::EastSP(int *y, int *x)
{
    int max = ROWS - 2;
    *x = COLUMNS - 2; 

    while (true)
    {
        *y = 1 + (rand() % max);

        if (IsVectorEmpty(y, x))
            break;

        if (PositionCheck(y, x))
            continue;

        break;
    }
}

// West spawn point.
void Spawn::WestSP(int *y, int *x)
{
    int max = ROWS - 2;
    *x = 1;

    while (true)
    {
        *y = 1 + (rand() % max);

        if (IsVectorEmpty(y, x))
            break;

        if (PositionCheck(y, x))
            continue;

        break;
    }
}

// South spawn point.
void Spawn::SouthSP(int *y, int *x)
{
    int max = COLUMNS - 2;
    *y = ROWS - 2;

    while (true)
    {
        *x = 1 + (rand() % max);

        if (IsVectorEmpty(y, x))
            break;

        if (PositionCheck(y, x))
            continue;

        break;
    }
}

// North spawn point.
void Spawn::NorthSP(int *y, int *x)
{
    // Step 1. Ready the variables.
    int max = COLUMNS - 2;
    *y = 1;

    while (true)
    {
        *x = 1 + (rand() % max);

        // Step 2. If Vector is empty, add the position to the vector. No need to move to step 3.
        if (IsVectorEmpty(y, x))
            break;

        // Step 3. Vector has previous entries, check if the new spawn position is occupied. If so, continue with a new x coordinate.
        if (PositionCheck(y, x))
            continue;

        break;
    }
}

void Spawn::SetSpawnDirection(int *y, int *x)
{
    // Step 1. Use random number select a spawn direction. (SP = Spawn point).
    m_spawnDirection = 0 + (rand() % 3);

    // Step 2. Apply random number.
    switch (m_spawnDirection)
    {
    case 0:
        NorthSP(y, x);
        break;
    case 1: 
        SouthSP(y, x);
        break;
    case 2: 
        WestSP(y, x);
        break;
    case 3: 
        EastSP(y, x);
        break;
    default:
        std::cout << "[Spawn.cpp] Error!\n";
        break;
    }
}

// Select a spawn position for an enemy.
void Spawn::SpawnPoint(int *y, int *x)
{
    // Step 1. Begin process to find spawn point.
    SetSpawnDirection(y, x);
}
