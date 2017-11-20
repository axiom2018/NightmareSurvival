// RocketLauncher.h
#pragma once
#include "Items.h"
#include "Definitions.h"

class RocketLauncher : public Items
{
private:
    const int m_id = ROCKET_LAUNCHER_ID;
    const std::string m_gunName = "RocketLauncher";
    int m_ammo;
public:
    RocketLauncher() : m_ammo(20) {};
    virtual int GetId() override { return m_id; }
    virtual int GetAmmo() override { return m_ammo; }
    virtual void SetAmmo(int ammo) override { m_ammo = ammo; }
    virtual void Reload(int magazine) override { m_ammo += magazine; }
    virtual void DecreaseAmmo() override { --m_ammo; }
    virtual std::string ItemName() const override { return m_gunName; }
};