// BorderManagement.cpp
#include "BorderManagement.h"

// Save important data that the player will give.
BorderManagement::BorderManagement(int *playerX, int *playerY, int worldWidth, int worldHeight)
{
    // Step 1. Players position will change of course, save in pointer.
    m_pX = playerX;
    m_pY = playerY;

    // Step 2. Save world information.
    m_worldWidth = worldWidth;
    m_worldHeight = worldHeight;
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
    int limit = m_worldHeight - 1;
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
    int limit = m_worldWidth - 1;
    int temp = *m_pX + 1;
    if (temp >= limit)
        return true;

    return false;
}

bool BorderManagement::CheckAreaForBorders(char key)
{
    switch (key)
    {
    case 'w':
        if (NorthBorderCheck())
            return true;
        break;
    case 'a':
        if (WestBorderCheck())
            return true;
        break;
    case 's':
        if (SouthBorderCheck())
            return true;
        break;
    case 'd':
        if (EastBorderCheck())
            return true;
        break;
    default:
        break;
    }

    return false;
}
