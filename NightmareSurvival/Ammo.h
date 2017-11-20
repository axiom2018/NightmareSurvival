// Ammo.h
#pragma once
#include "Items.h"
#include "Definitions.h"

class Ammo : public Items
{
private:
    const std::string m_name = "Ammo";
    const int m_id = AMMUNITION_ID;
    int m_magazine;
public:
    Ammo() { m_magazine = AMMO_UPGRADE; };
    virtual int GetId() override { return m_id; }
    virtual std::string ItemName() const override { return m_name; }
    virtual int GetUpgradeAmount() const { return m_magazine; };
    virtual ~Ammo() {};
};