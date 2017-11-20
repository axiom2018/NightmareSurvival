// CursorManager.cpp
#include "CursorManager.h"
#include "CursorGUIControls.h"
#include <iostream>
#include <windows.h>

// Init necessary variables in constructor.
CursorManager::CursorManager() :
    m_cursor('S'),
    m_marker(' '),
    m_currentChosenIndex(0),
    m_max(0),
    m_maxDownwardMovement(0)
{
    
}

void CursorManager::NormalCursorMovement(int * pIndex, char direction)
{
    switch (direction)
    {
    case m_up:
        *pIndex -= 1;
        break;
    case m_down:
        *pIndex += 1;
        break;
    default:
        std::cout << "Invalid direction!\n";
        break;
    }
}

void CursorManager::MoveCursorDown(int * pIndex, char direction)
{
    switch (direction)
    {
    case m_up:
        *pIndex -= 1;
        break;
    case m_down:
        *pIndex = 0;
        break;
    default:
        std::cout << "Invalid direction!\n";
        break;
    }
}

void CursorManager::MoveCursorUp(int * pIndex, char direction)
{
    switch (direction)
    {
    case m_up:
        *pIndex = m_maxDownwardMovement - 1;
        break;
    case m_down:
        *pIndex += 1;
        break;
    default:
        std::cout << "Invalid direction!\n";
        break;
    }
}

// Process the players selection.
void CursorManager::Selection(int * pIndex, char direction)
{
    if (*pIndex == 0)
    {
        MoveCursorUp(pIndex, direction);
        return;
    }

    else if (*pIndex == m_maxDownwardMovement - 1)
    {
        MoveCursorDown(pIndex, direction);
        return;
    }

    NormalCursorMovement(pIndex, direction);
}

// A client of this interface will provide the character the user input.
int CursorManager::ProcessPlayerInput(char input, int maxDownwardMovement)
{
    // Step 1. Save maxDownward movement for later use.
    m_maxDownwardMovement = maxDownwardMovement;

    // Step 2. Process input.
    switch (input)
    {
    case m_up:
        Selection(&m_currentChosenIndex, m_up);
        break;
    case m_down:
        Selection(&m_currentChosenIndex, m_down);
        break;
    case m_select: // Return true if player presses select, if so, either cycle weapons or Vendor will do what they need to do.
        return true;
    case m_quit:
        system("cls");
        return false;
    default:
        break;
    }

    return -1;
}

// Referenced in CycleWeapons.cpp.
int CursorManager::GetChosenIndex() const
{
    return m_currentChosenIndex;
}

// Referenced in CycleWeapons.cpp.
char CursorManager::GetSymbol(int index)
{
    if (index == GetChosenIndex())
    {
        return m_cursor;
    }

    return m_marker;
}
