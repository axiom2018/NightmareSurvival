// FirstAid.h
#pragma once
#include "Items.h"
#define FIRST_AID_ID 3

class FirstAid : public Items
{
private:
    std::string m_name = "First Aid";
    const int m_id = FIRST_AID_ID;
    int m_amountToHeal;
public:
    FirstAid() : m_amountToHeal(20) {};
    virtual int GetId() override { return m_id; }
    virtual int GetUpgradeAmount() const { return m_amountToHeal; };
    virtual std::string ItemName() const override { return m_name; }
    virtual ~FirstAid() {};
};