// PlayerAlgorithms.h
#pragma once
#include <vector>

class PlayerAlgorithms
{
public:
    PlayerAlgorithms() {};
    virtual bool CycleWeaponry(std::vector<class Items*> pPlayerInventory, class Items &pPlayerCurrentWeapon) = 0;
    virtual ~PlayerAlgorithms() {};
};