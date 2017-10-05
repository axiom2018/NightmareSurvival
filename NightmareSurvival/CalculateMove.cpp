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

// Calculate where the enemy should move next.

// Initialize settings with constructor.
CalculateMove::CalculateMove(int enemySpeedDelay, int enemyDamage)
{
    m_ppWorld = World::Instance()->GetSpace();
    m_width = World::Instance()->GetWidth();
    m_height = World::Instance()->GetHeight();
    m_delay = enemySpeedDelay;
    m_maxDelay = enemySpeedDelay;
    m_enemyDamage = enemyDamage;
    m_initFuncPointers = false;
}

// Send damage to player.
void CalculateMove::ApplyDamage(int *x, int *y)
{
    // Step 1. Get player position.
    std::pair<int, int> playerPos = World::Instance()->GetPlayerPosition();

    // Step 2. If players position matches an enemys positon then apply proper damage.
    if (playerPos.second == *x
        && playerPos.first == *y)
    {
        World::Instance()->GetPlayer()->Damage(m_enemyDamage);
    }
}

// Enemy cannot move into the wall.
bool CalculateMove::BorderCheck(int index)
{
    if (m_ppWorld[index]->GetChar() == '#') // Update: Put this character in World.cpp.
        return true;
    
    return false;
}

// Part of the pre requisite tests.
bool CalculateMove::EnemiesCheck(int index)
{
    for (std::vector<std::pair<int, int>>::iterator it = m_enemyPositions.begin(); it != m_enemyPositions.end(); ++it)
    {
        int enemyIndex = (it->second * m_width) + it->first;
        if (enemyIndex == index)
        {
            return true;
        }
    }

    return false;
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

// Give enemy a lower position relative to it's current position.
void CalculateMove::AppointLowPosition(int arrIndex, int *x, int *y)
{
    // Step 1. Using the arrIndex in the below switch, indicate which low position enemy should be assigned.
    *y = *y + 1;

    // Step 2. Assign low position.
    switch (arrIndex)
    {
    case 0:
        *x = *x - 1;
        break;
    case 1:
        break;
    case 2:
        *x = *x + 1;
        break;
    default:
        std::cout << "Appoint Low Position Error!\n";
        break;
    }
}

// Give enemy a mid level position relative to it's current position.
void CalculateMove::AppointMidPosition(int arrIndex, int *x)
{
    // Step 1. Using the arrIndex in the below switch, indicate which high position enemy should be assigned.
    switch (arrIndex)
    {
    case 0:
        *x = *x - 1;
        break;
    case 1:
        *x = *x + 1;
        break;
    default:
        std::cout << "Appoint Mid Position Error!\n";
        break;
    }
}

// Give enemy a higher position relative to it's current position.
void CalculateMove::AppointHighPosition(int arrIndex, int *x, int *y)
{
    // Step 1. Using the arrIndex in the below switch, indicate which high position enemy should be assigned.
    *y = *y - 1;

    // Step 2. Assign high position.
    switch (arrIndex)
    {
    case 0:
        *x = *x - 1;
        break;
    case 1:
        break;
    case 2:
        *x = *x + 1;
        break;
    default:
        std::cout << "Appoint High Position Error!\n";
        break;
    }
}

// Decide where to move enemy based on altitude.
void CalculateMove::ResolveAltitude(EnemyAltitudes alt, int arrIndex, int *x, int *y)
{
    // Step 1. Switch determines whether we go high, low, or mid.
    switch (alt)
    {
    case EnemyAltitudes::Low:
        AppointLowPosition(arrIndex, x, y);
        break;
    case EnemyAltitudes::Mid:
        AppointMidPosition(arrIndex, x);
        break;
    case EnemyAltitudes::High:
        AppointHighPosition(arrIndex, x, y);
        break;
    default:
        break;
    }
}

// Important step before assigning position.
bool CalculateMove::AltitudeCheckAssistance(int posArr[], int arrSize, int outerLoop, int innerLoop, int *x, int *y, EnemyAltitudes alt)
{
    int i;
    for (int n = 0; n < outerLoop; ++n)
    {
        for (i = 0; i < innerLoop; ++i)
        {
            if ((this->*PrereqTests[i])(posArr[n]))
            {
                break;
            }
        }

        if (i == innerLoop)
        {
            // (Optional Step) If code has ran through above loop with no match, we can assign that position to the enemy.
            ResolveAltitude(alt, n, x, y);
            return true;
        }
    }

    return false;
}

// Calculate high positions.
bool CalculateMove::CheckHigh(int *x, int *y)
{
    // Step 1. Gather all coordinates above the enemy.
    Coordinates topLeft, topMiddle, topRight;
    topLeft.first = *x - 1;
    topLeft.second = *y - 1;

    topMiddle.first = *x;
    topMiddle.second = *y - 1;

    topRight.first = *x + 1;
    topRight.second = *y - 1;

    // Step 2. Calculate indexes. 
    int topLeftIndex = (topLeft.second * m_width) + topLeft.first;
    int topMiddleIndex = (topMiddle.second * m_width) + topMiddle.first;
    int topRightIndex = (topRight.second * m_width) + topRight.first;

    // Step 3. Use array for indexes using them later to validate potential positions for the enemy.
    int positions[HIGH_AND_LOW_MAX];
    positions[0] = topLeftIndex;
    positions[1] = topMiddleIndex;
    positions[2] = topRightIndex;

    // Step 4. Check the altitude again.
    if (AltitudeCheckAssistance(positions, HIGH_AND_LOW_MAX, HIGH_AND_LOW_MAX, MAX_PREREQ_TESTS, x, y, EnemyAltitudes::High))
    {
        return true;
    }

    return false;
}

// Calculate mid positions.
bool CalculateMove::CheckMid(int *x, int *y)
{
    // Step 1. Gather positions left and right of enemy.
    Coordinates left, right;
    left.first = *x - 1;
    left.second = *y;

    right.first = *x + 1;
    right.second = *y;

    // Step 2. Gather indexes.
    int leftIndex = (left.second * m_width) + left.first;
    int rightIndex = (right.second * m_width) + right.first;

    // Step 3. Use array for indexes using them later to validate potential positions for the enemy.
    int positions[MAX_PREREQ_TESTS];
    positions[0] = leftIndex;
    positions[1] = rightIndex;

    // Step 4. Check the altitude again.
    if (AltitudeCheckAssistance(positions, MAX_PREREQ_TESTS, MAX_PREREQ_TESTS, MAX_PREREQ_TESTS, x, y, EnemyAltitudes::Mid))
    {
        return true;
    }

    return false;
}

// Calculate low positions.
bool CalculateMove::CheckLow(int *x, int *y)
{
    // Step 1. Gather all coordinates below the enemy.
    Coordinates lowLeft, lowMiddle, lowRight;
    lowLeft.first = *x - 1;
    lowLeft.second = *y + 1;

    lowMiddle.first = *x;
    lowMiddle.second = *y + 1;

    lowRight.first = *x + 1;
    lowRight.second = *y + 1;

    // Step 2. Calculate indexes.
    int lowLeftIndex = (lowLeft.second * m_width) + lowLeft.first;
    int lowMiddleIndex = (lowMiddle.second * m_width) + lowMiddle.first;
    int lowRightIndex = (lowRight.second * m_width) + lowRight.first;

    // Step 3. Use array for indexes using them later to validate potential positions for the enemy.
    int positions[HIGH_AND_LOW_MAX];
    positions[0] = lowLeftIndex;
    positions[1] = lowMiddleIndex;
    positions[2] = lowRightIndex;

    // Step 4. Check the altitude again.
    if (AltitudeCheckAssistance(positions, HIGH_AND_LOW_MAX, HIGH_AND_LOW_MAX, MAX_PREREQ_TESTS, x, y, EnemyAltitudes::Low))
    {
        return true;
    }

    return false;
}

// Incase a position is taken, look around.
bool CalculateMove::CheckSurroundings(int *x, int *y)
{
    for (int i = 0; i < MAX_POSITION_TESTS; ++i)
    {
        if ((this->*PrimaryPositionTest[i])(x, y))
        {
            break;
        }
    }

    return true;
}

// If empty, this will be cleared in the IsPositionTaken() function.
bool CalculateMove::CheckEnemySize() const
{
    if (m_enemyPositions.empty())
        return true;

    return false;
}

bool CalculateMove::IsPositionTaken(int x, int y)
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

// Give enemy their desired position.
void CalculateMove::AppointPosition(int *x, int *y)
{
    if (!IsPositionTaken(m_desiredPosition.first, m_desiredPosition.second))
    {
        *x = m_desiredPosition.first;
        *y = m_desiredPosition.second;
    }

    else
    {
        CheckSurroundings(x, y);
    }
}

// Check if player is to the right of enemy.
void CalculateMove::CheckRight(Coordinates player, int *x, int *y)
{
    // Step 1. Adjust desired position.
    m_desiredPosition.first = *x + 1;

    // Step 2. Check up, middle, or down.
    if (player.second < *y) // Player is above the enemy.
    {
        m_desiredPosition.second = *y - 1;
    }

    else if (player.second > *y) // Player is below the enemy.
    {
        m_desiredPosition.second = *y + 1;
    }

    else if (player.second == *y) // Player is on the same y as the enemy.
    {
        m_desiredPosition.second = *y;
    }

    // Step 3. Attempt to assign position.
    AppointPosition(x, y);
}

void CalculateMove::CheckMiddle(Coordinates player, int *x, int *y)
{
    // Step 1. Adjust desired position.
    m_desiredPosition.first = *x;

    // Step 2. Check left or right.
    if (player.second < *y) // Check above.
    {
        m_desiredPosition.second = *y - 1;
    }

    else if (player.second > *y) // Check below.
    {
        m_desiredPosition.second = *y + 1;
    }


    // Step 3. Attempt to assign position.
    AppointPosition(x, y);
}

void CalculateMove::CheckLeft(Coordinates player, int *x, int *y)
{
    m_desiredPosition.first = *x - 1;

    // Step 1. Check up, middle, or down.
    if (player.second < *y) // Player is above the enemy.
    {
        m_desiredPosition.second = *y - 1;
    }

    else if (player.second > *y) // Player is below the enemy.
    {
        m_desiredPosition.second = *y + 1;
    }

    else if (player.second == *y) // Player is on the same y as the enemy.
    {
        m_desiredPosition.second = *y;
    }

    // Step 3. Attempt to assign position.
    AppointPosition(x, y);
}

void CalculateMove::CheckXPos(Coordinates player, int *x, int *y)
{
    // Step 1. Is player to the enemy's left, right, or is the enemy sharing the same x position?
    if (player.first < *x) // Left.
    {
        CheckLeft(player, x, y);
    }

    else if (player.first > *x) // Right.
    {
        CheckRight(player, x, y);
    }

    else if (player.first == *x) // Middle.
    {
        CheckMiddle(player, x, y);
    }
}

void CalculateMove::InitFuncPointers()
{
    // Step 1. Assign func pointers proper values.
    PrimaryPositionTest[0] = &CalculateMove::CheckHigh;
    PrimaryPositionTest[1] = &CalculateMove::CheckMid;
    PrimaryPositionTest[2] = &CalculateMove::CheckLow;

    PrereqTests[0] = &CalculateMove::BorderCheck;
    PrereqTests[1] = &CalculateMove::EnemiesCheck;

    // Step 2. Change m_initFuncPointer6s to true instead of false.
    m_initFuncPointers = true;
}

void CalculateMove::CalculateEnemyMove(int *x, int *y)
{
    // Step 1. Check delay.
    if (!DelayCheck())
        return;

    // Step 2. Init the function pointers necessary for position testing.
    if (!m_initFuncPointers)
        InitFuncPointers();

    // Step 3. Reset the delay speed.
    m_delay = m_maxDelay;

    // Step 4. Continue with move calculation process by getting player position.
    Coordinates playerPos; 
    playerPos.first = World::Instance()->GetPlayerPosition().second;
    playerPos.second = World::Instance()->GetPlayerPosition().first;

    // Step 5. Check the x position.
    CheckXPos(playerPos, x, y);

    // Step 6. Apply damage if necessary.
    ApplyDamage(x, y);
}