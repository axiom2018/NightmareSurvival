// CursorManager.h
#pragma once

/* What is CursorManager? It's an interface for the user to make a selection between listed components. Like a person at a restaurant 
looking the  menu, trying to decide what they want. The person will probably look up and down until they've selected the dish 
they'll like to purchase and consume. The same principle applies here. 

Why was this necessary? As of the date provided early in this comment, there are 2 classes that actually use a VERY similiar cursor system,
with slight differences. Those classes are CycleWeapons.h and Vendor.h. Removing those separate inner implementations of a cursor system, 
and forcing them to both refer to this interface will not only cut code, but delegate the overall responsibilty to ANY future classes that
wish to use a cursor system as well. */

class CursorManager
{
    char m_cursor;
    char m_marker;
    int m_currentChosenIndex;
    int m_max;
    int m_maxDownwardMovement;

    void NormalCursorMovement(int *pIndex, char direction);
    void MoveCursorDown(int *pIndex, char direction);
    void MoveCursorUp(int *pIndex, char direction);
    void Selection(int *pIndex, char direction);
public:
    CursorManager();
    int ProcessPlayerInput(char input, int maxDownwardMovement);
    int GetChosenIndex() const;
    char GetSymbol(int index);
};