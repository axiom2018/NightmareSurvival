// Items.h
#pragma once
#include <iostream>

class Items
{
public:
    virtual void Draw() const {};
    virtual int GetId() = 0;
    virtual int GetAmmo() { return 0; }
    virtual void Reload(int magazine) {}
    virtual void DecreaseAmmo() {};
    virtual std::string ItemName() const = 0;
    virtual int GetUpgradeAmount() const { return 0; };
    virtual ~Items() {}
};