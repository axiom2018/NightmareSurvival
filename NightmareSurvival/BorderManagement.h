// BorderManagement.h
#pragma once

// In the old implementation, the player checked for borders before movement. Delegate that responsibility to this class.

class BorderManagement
{
    // Necessary variables/functions to control do border managing that include pointer to player position and world information.
    int *m_pX;
    int *m_pY;
    int m_worldWidth;
    int m_worldHeight;

    bool NorthBorderCheck();
    bool SouthBorderCheck();
    bool WestBorderCheck();
    bool EastBorderCheck();
public:
    BorderManagement(int *playerX, int *playerY);
    bool CheckAreaForBorders(char key);
};