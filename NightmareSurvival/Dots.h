// Dots.h
#pragma once
#include "Entities.h"

// Dots make up the game board, play will walk on them.

class Dots : public Entities
{
private:
    char m_dot = '.';
public:
    virtual void Draw() const override;
    virtual char GetChar() const override;
};