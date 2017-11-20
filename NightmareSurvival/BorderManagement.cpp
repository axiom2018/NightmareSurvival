// BorderManagement.cpp
#include "BorderManagement.h"
#include "PlayerGameControls.h"
#include "Definitions.h"

// Save important data that the player will give.
BorderManagement::BorderManagement(int *playerX, int *playerY)
{
    // Step 1. Players position will change of course, save in pointer.
    m_pX = playerX;
    m_pY = playerY;
}

bool BorderManagement::NorthBorderCheck()
{
    int temp = *m_pY - 1;
    if (temp <= 0)
        return true;

    return false;
}

bool BorderManagement::SouthBorderCheck()
{
    int limit = ROWS - 1;
    int temp = *m_pY + 1;
    if (temp >= limit)
        return true;

    return false;
}

bool BorderManagement::WestBorderCheck()
{
    int temp = *m_pX - 1;
    if (temp <= 0)
        return true;

    return false;
}

bool BorderManagement::EastBorderCheck()
{
    int limit = COLUMNS - 1;
    int temp = *m_pX + 1;
    if (temp >= limit)
        return true;

    return false;
}

bool BorderManagement::CheckAreaForBorders(char key)
{
    switch (key)
    {
    case m_up:
        if (NorthBorderCheck())
            return true;
        break;
    case m_left:
        if (WestBorderCheck())
            return true;
        break;
    case m_down:
        if (SouthBorderCheck())
            return true;
        break;
    case m_right:
        if (EastBorderCheck())
            return true;
        break;
    default:
        break;
    }

    return false;
}
