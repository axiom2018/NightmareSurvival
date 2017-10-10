// PlayerAlgorithms.h
#pragma once
#include <vector>

// No need for this to be a Base class and CycleWeapons.h/.cpp to be a subclass, when CycleWeapons is the ONLY one inheriting.

class PlayerAlgorithms
{
public:
    PlayerAlgorithms() {};
    virtual bool CycleWeaponry(std::vector<class Items*> pPlayerInventory, class Items &pPlayerCurrentWeapon) = 0;
    virtual ~PlayerAlgorithms() {};
};