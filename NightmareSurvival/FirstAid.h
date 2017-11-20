// FirstAid.h
#pragma once
#include "Items.h"
#include "Definitions.h"

class FirstAid : public Items
{
private:
    std::string m_name = "First Aid";
    const int m_id = FIRSTAID_ID;
    int m_amountToHeal;
public:
    FirstAid() { m_amountToHeal = FIRST_AID_UPGRADE; };
    virtual int GetId() override { return m_id; }
    virtual int GetUpgradeAmount() const { return m_amountToHeal; };
    virtual std::string ItemName() const override { return m_name; }
    virtual ~FirstAid() {};
};