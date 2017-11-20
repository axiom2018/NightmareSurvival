// UpgradeStrategy.h
#pragma once

// Note: UpgradeStrategy will serve the simple purpose of carrying out how certain upgrades go about their business. 

class UpgradeStrategy
{
public:
    virtual void Use(class Items *pItem, class WeaponManager *pWeaponManager) = 0;
};
