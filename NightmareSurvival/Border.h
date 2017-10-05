// Border.h
#pragma once
#include "Entities.h"

// The border of the game where the player, nor enemies can get past.

class Border : public Entities
{
    char m_border = '#';
public:
    virtual void Draw() const override;
    virtual char GetChar() override;
};