// CheckArea.cpp
#include "CheckArea.h"
#include "Coordinates.h"
#include "World.h"
#include "EnemyManagement.h"
#include "Enemies.h"

// Initialize function pointers.
CheckArea::CheckArea(std::vector<Coordinates> *pEnemyCoordinates)
{
    // Step 1. Assign primary position test function pointers proper values.
    PrimaryPositionTest[0] = &CheckArea::CheckHigh;
    PrimaryPositionTest[1] = &CheckArea::CheckMid;
    PrimaryPositionTest[2] = &CheckArea::CheckLow;

    // Step 2. Assign prerequisite tests function pointers proper values.
    PrereqTests[0] = &CheckArea::BorderCheck;
    PrereqTests[1] = &CheckArea::EnemiesCheck;

    // Step 3. Save the pointer to the enemy coordinaters given to us by ManageEnemyPosition.
    m_pEnemyCoordinates = pEnemyCoordinates;
}

// Enemies can't move into the border of the game.
bool CheckArea::BorderCheck(int index)
{
    if (World::Instance()->CheckBorder(index))
        return true;

    return false;
}

// Cross check enemy positions with current enemy position.
bool CheckArea::EnemiesCheck(int index)
{
    for (std::vector<Coordinates>::iterator it = m_pEnemyCoordinates->begin(); it != m_pEnemyCoordinates->end(); ++it)
    {
        int enemyIndex = (it->second * COLUMNS) + it->first;
        if (enemyIndex == index)
        {
            return true;
        }
    }

    return false;
}

// Give enemy a lower position relative to it's current position.
void CheckArea::AppointLowPosition(int arrIndex, int * x, int * y)
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
        break;
    }
}

// Give enemy a mid level position relative to it's current position.
void CheckArea::AppointMidPosition(int arrIndex, int * x)
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
        break;
    }
}

// Give enemy a higher position relative to it's current position.
void CheckArea::AppointHighPosition(int arrIndex, int * x, int * y)
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
        break;
    }
}

// Apply position to enemy.
void CheckArea::ResolveAltitude(EnemyAltitudes alt, int arrIndex, int * x, int * y)
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

// Run Prereq tests (BorderCheck and EnemiesCheck) to determine position.
bool CheckArea::AltitudeCheckAssistance(int posArr[], int arrSize, int outerLoop, int innerLoop, int * x, int * y, EnemyAltitudes alt)
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
            //  If code has ran through above loop with no match, we can assign that position to the enemy.
            ResolveAltitude(alt, n, x, y);
            return true;
        }
    }

    return false;
}

// Calculate all positions above the enemy.
bool CheckArea::CheckHigh(int * x, int * y)
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
    int topLeftIndex = (topLeft.second * COLUMNS) + topLeft.first;
    int topMiddleIndex = (topMiddle.second * COLUMNS) + topMiddle.first;
    int topRightIndex = (topRight.second * COLUMNS) + topRight.first;

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

// Calculate positions on both sides of the enemy.
bool CheckArea::CheckMid(int * x, int * y)
{
    // Step 1. Gather positions left and right of enemy.
    Coordinates left, right;
    left.first = *x - 1;
    left.second = *y;

    right.first = *x + 1;
    right.second = *y;

    // Step 2. Gather indexes.
    int leftIndex = (left.second * COLUMNS) + left.first;
    int rightIndex = (right.second * COLUMNS) + right.first;

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

// Calculate all positions below the enemy.
bool CheckArea::CheckLow(int * x, int * y)
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
    int lowLeftIndex = (lowLeft.second * COLUMNS) + lowLeft.first;
    int lowMiddleIndex = (lowMiddle.second * COLUMNS) + lowMiddle.first;
    int lowRightIndex = (lowRight.second * COLUMNS) + lowRight.first;

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

// Begin process of finding any surrounding position since previously desired position was occupied.
bool CheckArea::CheckSurroundingArea(int * x, int * y)
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
