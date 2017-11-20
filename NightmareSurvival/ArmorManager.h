// ArmorManager.h
#pragma once

// Delegate responsibility of player's armor to this interface.

class ArmorManager
{
    int m_armor;
public:
    ArmorManager();
    int GetArmor() const;
    void SetArmor(int armor);
    bool DamageArmor(int damage);
};