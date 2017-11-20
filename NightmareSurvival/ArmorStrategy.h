// ArmorStrategy.h
#pragma once
#include "UpgradeStrategy.h"

class ArmorStrategy : public UpgradeStrategy
{
public:
    virtual void Use(class Items * pItem, class WeaponManager *pWeaponManager) override;
};