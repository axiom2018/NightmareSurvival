// Armor.h
#pragma once
#include "Items.h"
#define ARMOR_ID 4

class Armor : public Items
{
private:
    const std::string m_name = "Armor";
    const int m_id = ARMOR_ID;
    int m_amountToBoostArmor;
public:
    Armor() : m_amountToBoostArmor(20) {};
    virtual int GetId() override { return m_id; }
    virtual int GetUpgradeAmount() const { return m_amountToBoostArmor; };
    virtual std::string ItemName() const override { return m_name; }
    virtual ~Armor() {};
};