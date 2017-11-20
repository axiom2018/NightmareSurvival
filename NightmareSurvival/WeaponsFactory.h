// WeaponsFactory.h 
#pragma once
#include "ItemsFactory.h"

// Factory pattern for game weaponry.

class WeaponsFactory : public ItemsFactory
{
public:
    virtual Items *GetItem(int choice) override;
};