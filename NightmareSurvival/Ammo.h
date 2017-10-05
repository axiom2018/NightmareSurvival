// Ammo.h
#pragma once
#include "Items.h"
#define AMMO_ID 5

class Ammo : public Items
{
private:
    const std::string m_name = "Ammo";
    const int m_id = AMMO_ID;
    int m_magazine;
public:
    Ammo() : m_magazine(20) {};
    virtual int GetId() override { return m_id; }
    virtual std::string ItemName() const override { return m_name; }
    virtual int GetUpgradeAmount() const { return m_magazine; };
    virtual ~Ammo() {};
};