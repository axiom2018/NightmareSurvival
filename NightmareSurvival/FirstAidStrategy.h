// FirstAidStrategy.h
#pragma once
#include "UpgradeStrategy.h"

class FirstAidStrategy : public UpgradeStrategy
{
public:
    virtual void Use(class Items * pItem, class WeaponManager *pWeaponManager) override;
};
