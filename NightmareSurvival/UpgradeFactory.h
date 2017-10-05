// UpgradeFactory.h
#pragma once
#include "ItemsFactory.h"

// Factory pattern for game upgrades.

class UpgradeFactory : public ItemsFactory
{
public:
    virtual Items *GetItem(int choice) override;
};