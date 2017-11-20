// Pistol.h
#pragma once
#include "Items.h"
#include "Definitions.h"

class Pistol : public Items
{
private:
    const int m_id = PISTOL_ID;
    const std::string m_gunName = "Pistol";
    int m_ammo;
public:
    Pistol() : m_ammo(15) {};
    virtual int GetId() override { return m_id; }
    virtual int GetAmmo() override { return m_ammo; }
    virtual void SetAmmo(int ammo) override { m_ammo = ammo; }
    virtual void Reload(int magazine) override { m_ammo += magazine; }
    virtual void DecreaseAmmo() override { --m_ammo; }
    virtual std::string ItemName() const override { return m_gunName; }
};