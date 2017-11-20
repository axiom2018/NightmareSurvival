// AmmoStrategy.h
#pragma once
#include "UpgradeStrategy.h"

class AmmoStrategy : public UpgradeStrategy
{
public:
    virtual void Use(class Items * pItem, class WeaponManager *pWeaponManager) override;
};
